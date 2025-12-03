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
	GameScene(physx::PxPhysics* gPhysics, physx::PxMaterial* gMaterial, physx::PxScene* gScene) : Scene(gPhysics, gMaterial, gScene) {};
	virtual void integrate(double t) override;
	virtual void init() override;
	virtual void keyPress(unsigned char key, const physx::PxTransform& camera) override;
	~GameScene();
protected:
	Gun* mGun = nullptr;
	Player* player;
	Volcano* volcano;
	ParticleSystem* cynder;
	WindGenerator* wind;

	Particle* p1;
	Particle* p2;
};
