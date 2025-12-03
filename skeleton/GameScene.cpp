#include "GameScene.h"

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Gun.h"
#include "ParticleSystem.h"
#include "UniformGeneration.h"
#include "GaussianGeneration.h"
#include "Explosion.h"
#include "GravityGenerator.h"
#include "Floor.h"
#include "Player.h"
#include "Volcano.h"
#include "ParabolicMover.h"
#include "WindGenerator.h"
#include "Scene.h"

void GameScene::integrate(double t) {
	mGun->Update(t);
	player->Update(t);

	volcano->Update(t);
	cynder->Update(t);

	Vector3 dir = player->getPos() - GetCamera()->getEye();
	GetCamera()->setPosition(player->getPos() + Vector3(0, 5, -80));
	GetCamera()->setDirection(dir.getNormalized());
	cynder->SetPosition(player->getPos() + Vector3(-80, -80, -80));
}

void GameScene::init() {
	mGun = new Gun({ 0, 0, 0 }, { 20, 20, 20 }, { 0, -9.8, 0 }, 10.0, 1.0, Particle::EULER, 10.0);

	player = new Player(new Particle(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.0, 0.0, 1.0, Particle::VERLET, Vector4(0, 0, 1, 1)));

	p1 = new Particle(Vector3(20, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.0, 0.0, 5.0, Particle::VERLET, Vector4(0, 1, 1, 1));
	p2 = new Particle(Vector3(-20, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.0, 0.0, 10.0, Particle::VERLET, Vector4(1, 0, 1, 1));

	Floor* floor = new Floor(Vector3(0, -1.5, 0), gScene);
	volcano = new Volcano(Vector3(0, 300, 900), player);

	std::vector<ParticleGen*> gens;
	gens.push_back(new UniformGeneration({ 0,0,0 }, { 0,0,0 }, 2, 1, 0, 200));
	std::vector<ForceGenerator*> forces;
	forces.push_back(new GravityGenerator({ 0,0,0 }, 0.3));
	wind = new WindGenerator({ 0,0,0 }, { 1000,1000,1000 }, { 400,50,5 });
	forces.push_back(wind);
	cynder = new ParticleSystem({ 0,0,0 }, gens, forces);
}

void GameScene::keyPress(unsigned char key, const physx::PxTransform& camera) {
	Vector3 player_dir = Vector3(0, 0, 0);
	if (toupper(key) == 'I') player_dir += Vector3(0, 0, 1);
	if (toupper(key) == 'K') player_dir += Vector3(0, 0, -1);
	if (toupper(key) == 'J') player_dir += Vector3(1, 0, 0);
	if (toupper(key) == 'L') player_dir += Vector3(-1, 0, 0);

	player->Move(player_dir);

	PxVec3 dir = camera.q.rotate({ 0,0,-1 });
	switch (toupper(key))
	{
	case 'B':
		mGun->SetPosition(camera.p + dir * 10);
		mGun->SetRotation(camera.q);
		mGun->Shoot();
		break;
	case 'F':
		wind->Toggle();
		break;
	default:
		break;
	}
}

GameScene::~GameScene() {
	delete cynder;
	delete player;
	delete volcano;
	delete p1;
	delete p2;
	delete mGun;
}