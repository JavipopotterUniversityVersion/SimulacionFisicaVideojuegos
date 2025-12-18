#include "SpringScene.h"
#include <PxPhysics.h>
#include "WindGenerator.h"
#include "ParticleGen.h"
#include "UniformGeneration.h"
#include "GaussianGeneration.h"
#include "GravityGenerator.h"
#include "ParticleSystem.h"
#include "DynamicParticleSystem.h"
#include "RigidCube.h"
#include "DynamicParticle.h"
#include "DynamicParticleCannon.h"
#include "Water.h"
#include "Explosion.h"

void SpringScene::init() {
	Particle* p = new Particle();
	//mSpring = new Spring(Vector3(20,20,0), p, 2.0f, 20.0f);

	floor = new Floor(Vector3(0, 0, 0), gScene);

    new RigidCube(Vector3(30, 0, 30), PxVec3(20, 5, 20), gScene, Vector4(1, 0, 0, 1));
    new RigidCube(Vector3(60, 0, 40), PxVec3(12, 10, 12), gScene, Vector4(0, 0, 1, 1));
    new RigidCube(Vector3(100, 0, 25), PxVec3(18, 15, 18), gScene, Vector4(1, 1, 0, 1));
    new RigidCube(Vector3(140, 0, 50), PxVec3(40, 3, 8), gScene, Vector4(0.5f, 0, 1, 1));
    new RigidCube(Vector3(180, 0, 60), PxVec3(6, 30, 6), gScene, Vector4(0, 1, 1, 1));


	diego = new Diego(gPhysics, gScene, Vector3(0,20,0));

    water = new Water(Vector3(0, 0, 100), Vector3(50, 20, 50));
    water->addTarget(diego->getPelvis());

    m_cannon = new DynamicParticleCannon(Vector3(0, 5, 15), gPhysics, gScene);
    m_cannon->toggle();
    cannons.push_back(m_cannon);

    DynamicParticle* particle = new DynamicParticle(gPhysics, gScene, Vector3(0, 5, 0));

    setupCynder();
    setupBallPool();
    setupEnemies();
}

void SpringScene::setupEnemies() {
    const int numEnemies = 30;
    const float radius = 100.0f;
    const float height = 20.0f;

    for (int i = 0; i < numEnemies; ++i) {
        float angle = PxTwoPi * i / numEnemies;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        Marco* enemy = new Marco(gPhysics, gScene, Vector3(x, height, z), Vector4(1,0,0,1));
        enemy->setTarget(diego->getHead());
        enemies.push_back(enemy);
        water->addTarget(enemy->getDiego()->getHead());
    }
}

void SpringScene::setupBallPool() {
    std::vector<ParticleGen*> gens;
    gens.push_back(new GaussianGeneration(Vector3(0,0,0), 1.0f, 1, 0));
    std::vector<ForceGenerator*> forces;
    wind2 = new WindGenerator({ 0,0,0 }, { 1000,1000,1000 }, { 0,1000,0 });
    explosion = new Explosion(Vector3(0, 0, 0), 50, 0.1, 1000);
    explosion->Disable();
    forces.push_back(explosion);
    forces.push_back(wind2);
    ball_pool = new DynamicParticleSystem(Vector3(0, 10, -25), gens, forces, gPhysics, gScene);
}

void SpringScene::setupCynder() {
    std::vector<ParticleGen*> gens;
    gens.push_back(new UniformGeneration({ 0,0,0 }, 2, 10, 0, 200));
    std::vector<ForceGenerator*> forces;
    //forces.push_back(new GravityGenerator({ 0,0,0 }, 0.3));
    //wind = new WindGenerator({ 0,0,0 }, { 1000,1000,1000 }, { 400,50,5 });
    //forces.push_back(wind);
    cynder = new ParticleSystem({ 0,0,0 }, gens, forces);
}

PxRigidDynamic* SpringScene::getNearestEnemy() {
    PxRigidDynamic* closest = nullptr;
    float minDistSqr = FLT_MAX;

    PxVec3 myPos = diego->getChest()->getGlobalPose().p;

    for (auto& enemy : enemies) {
        if (!enemy) continue;

        PxVec3 ePos = enemy->getDiego()->getChest()->getGlobalPose().p;
        float distSqr = (ePos - myPos).magnitudeSquared();

        if (distSqr < minDistSqr) {
            minDistSqr = distSqr;
            closest = enemy->getDiego()->getChest();
        }
    }

    return closest;
}


void SpringScene::integrate(double t) {
	//mSpring->integrate(t);x
    m_cannon->setTarget(getNearestEnemy());

    cynder->Update(t);
    cynder->SetPosition(diego->getPos() - Vector3(100,0,100));
    ball_pool->Update(t);

	diego->integrate(t);
    water->integrate(t);

    for (auto cannon : cannons) {
        cannon->Update(t);
    }

    for (auto diego : enemies) {
        diego->integrate(t);
    }

    m_cannon->SetPosition(diego->getPos() + Vector3(0, 5, 0));
    //cynder->SetPosition(diego->getPos());
    updateCamera();
}

void SpringScene::updateCamera() {
    PxVec3 diego_pos = diego->getPos();
    PxVec3 direction = diego_pos - GetCamera()->getEye();
    direction = direction.getNormalized();

    float distance = 10.0f;
    float height = 4.0f;

    PxVec3 cam_offset = PxVec3(
        -sinf(cameraYaw) * distance,
        height,
        -cosf(cameraYaw) * distance
    );

    PxVec3 camPos = diego_pos + cam_offset;

    GetCamera()->setPosition(camPos);
    GetCamera()->setDirection(direction);
}

void SpringScene::keyPress(unsigned char key, const physx::PxTransform& camera) {
    physx::PxVec3 forward = camera.q.getBasisVector2();

    physx::PxVec3 right = physx::PxVec3(-forward.z, 0, forward.x);
    right.normalize();

    forward.y = 0;
    right.y = 0;

    forward.normalize();
    right.normalize();

    if (key == 'g')
        diego->move(forward);
    else if (key == 't')
        diego->move(-forward);
    else if (key == 'h')
        diego->move(-right);
    else if (key == 'f')
        diego->move(right);
    else if (key == ' ')
        diego->jump();
    else if (key == 'l')
        cameraYaw -= cameraRotateSpeed;
    else if (key == 'j')
        cameraYaw += cameraRotateSpeed;
    else if (key == 'k')
        explosion->Enable();
    else if (key == 'i')
        wind2->Toggle();
    else if (key == 'v')
        diego->toggle_play_dead();
    else if (key == 'c')
        m_cannon->toggle();
}

SpringScene::~SpringScene() {
	delete diego;
    delete floor;
    delete water;
    delete cynder;
    delete wind;

    for (auto cube : cubes) {
        delete cube;
    }

    for (auto marco : enemies) {
        delete marco;
    }

    for (auto canon : cannons) {
        delete canon;
    }
}
