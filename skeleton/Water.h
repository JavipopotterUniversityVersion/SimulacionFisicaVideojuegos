#pragma once
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include "core.hpp"

class Water
{
private:
	const float LIQUID_DENSITY = 350.0f;

	RenderItem* item = nullptr;
	physx::PxTransform* position = nullptr;

	std::vector<physx::PxRigidDynamic*> targets;
public:
	Water(Vector3 pos, Vector3 halfExtents = Vector3(10.0f, 10.0f, 10.0f));
	~Water() {};

	void addTarget(physx::PxRigidDynamic*);
	void integrate(float t);

	bool isInside(physx::PxRigidDynamic* target);
};

