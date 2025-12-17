#pragma once
#include "Scene.h"
#include "Spring.h"
#include "Diego.h"
#include "Marco.h"
#include "Floor.h"

class ParticleSystem;
class WindGenerator;
class RigidCube;
class DynamicParticleCannon;
class Water;

class SpringScene : public Scene
{
private:
	Diego* diego;
	Water* water;
	std::vector<Marco*> enemies;

	Spring* mSpring;
	Floor* floor;
	std::vector<RigidCube*> cubes;
	std::vector<DynamicParticleCannon*> cannons;

	ParticleSystem* cynder;
	WindGenerator* wind;

	float cameraYaw = 0.0f;
	const float cameraRotateSpeed = 0.05f;
public:
	SpringScene(PxPhysics* gPhysics, PxMaterial* gMaterial, PxScene* gScene) : Scene(gPhysics, gMaterial, gScene) {};
	virtual void integrate(double t) override;
	virtual void init() override;
	virtual void keyPress(unsigned char key, const physx::PxTransform& camera) override;
	~SpringScene();

	void setupCynder();
	void setupEnemies();
	void updateCamera();
};

