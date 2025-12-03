#pragma once
#include <vector>
#include <PxPhysicsAPI.h>

class Scene
{
protected:
	physx::PxPhysics* gPhysics = NULL;
	physx::PxMaterial* gMaterial = NULL;
	physx::PxScene* gScene = NULL;
public:
	Scene(physx::PxPhysics* gPhysics, physx::PxMaterial* gMaterial, physx::PxScene* gScene) : gPhysics(gPhysics), gMaterial(gMaterial), gScene(gScene) {};
	virtual void integrate(double t) = 0;
	virtual void init() = 0;
	virtual void keyPress(unsigned char key, const physx::PxTransform& camera) {}
	virtual ~Scene();
};
