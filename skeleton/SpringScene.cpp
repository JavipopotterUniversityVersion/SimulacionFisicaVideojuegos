#include "SpringScene.h"
#include <PxPhysics.h>
#include "WindGenerator.h"
#include "ParticleGen.h"
#include "UniformGeneration.h"
#include "GravityGenerator.h"
#include "ParticleSystem.h"

void SpringScene::init() {
	Particle* p = new Particle();
	//mSpring = new Spring(Vector3(20,20,0), p, 2.0f, 20.0f);

	floor = new Floor(Vector3(0, 0, 0), gScene);
	diego = new Diego(gPhysics, gScene, Vector3(0,20,0));

    std::vector<ParticleGen*> gens;
    gens.push_back(new UniformGeneration({ 0,0,0 }, { 0,0,0 }, 2, 1, 0, 200));
    std::vector<ForceGenerator*> forces;
    forces.push_back(new GravityGenerator({ 0,0,0 }, 0.3));
    wind = new WindGenerator({ 0,0,0 }, { 1000,1000,1000 }, { 400,50,5 });
    forces.push_back(wind);
    cynder = new ParticleSystem({ 0,0,0 }, gens, forces);
}

void SpringScene::integrate(double t) {
	//mSpring->integrate(t);
    cynder->Update(t);
	diego->integrate(t);
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
}

SpringScene::~SpringScene() {
	delete diego;
}
