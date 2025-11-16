#pragma once
#include <vector>
#include <PxPhysicsAPI.h>

class Scene
{
public:
	Scene();
	virtual void integrate(double t) = 0;
	virtual void init() = 0;
	virtual void keyPress(unsigned char key, const physx::PxTransform& camera) {}
	virtual ~Scene();
protected:
};
