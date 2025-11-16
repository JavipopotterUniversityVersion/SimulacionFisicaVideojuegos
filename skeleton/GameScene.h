#pragma once
#include "Scene.h"

class Gun;
class Volcano;
class Player;
class ParticleSystem;
class WindGenerator;
class Particle;

class GameScene : public Scene
{
public:
	GameScene();
	virtual void integrate(double t);
	virtual void init();
	virtual void keyPress(unsigned char key, const physx::PxTransform& camera) {}
	virtual ~GameScene();
protected:
	Gun* mGun = nullptr;
	Player* player;
	Volcano* volcano;
	ParticleSystem* cynder;
	WindGenerator* wind;

	Particle* p1;
	Particle* p2;
};
