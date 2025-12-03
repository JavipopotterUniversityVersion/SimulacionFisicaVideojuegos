#pragma once
#include <PxRigidDynamic.h>
#include <PxPhysicsAPI.h>
#include <PxPhysics.h>
#include "core.hpp"

class RenderItem;

class Diego
{
private:
	RenderItem* item = NULL;
	physx::PxTransform* diego_tr = NULL;
	physx::PxRigidDynamic* rb = NULL;
public:
	Diego(physx::PxPhysics* gPhysics, physx::PxScene* gScene, Vector3 pos);
	~Diego() {
		delete item;
		delete diego_tr;
	};
};


