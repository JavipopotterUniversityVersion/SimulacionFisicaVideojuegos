#pragma once
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

using namespace physx;

class RigidCube {
private:
	PxRigidStatic* rb = nullptr;
	RenderItem* item = nullptr;
	PxTransform* position = nullptr;
	PxVec3 halfExtents;

public:
	RigidCube(Vector3 pos, PxVec3 size, PxScene* gScene, Vector4 color = Vector4(0, 1, 0, 1)) : halfExtents(size * 0.5f)
	{
		PxVec3 adjustedPos = PxVec3(pos.x, pos.y + halfExtents.y, pos.z);
		position = new PxTransform(adjustedPos);

		rb = PxGetPhysics().createRigidStatic(*position);
		auto geometry = PxBoxGeometry(halfExtents);
		auto shape = CreateShape(geometry);

		rb->attachShape(*shape);
		gScene->addActor(*rb);
		item = new RenderItem(shape, rb, color);
	}

	~RigidCube() {
		DeregisterRenderItem(item);
		item = nullptr;
		position = nullptr;
	}

	void setPos(Vector3 new_pos) {
		position->p = PxVec3(new_pos.x, new_pos.y + halfExtents.y, new_pos.z);
		rb->setGlobalPose(*position);
	}

	Vector3 getPos() {
		PxVec3 top = position->p;
		return Vector3(top.x, top.y - halfExtents.y, top.z);
	}

	PxVec3 getSize() const {
		return halfExtents * 2.0f;
	}
};
