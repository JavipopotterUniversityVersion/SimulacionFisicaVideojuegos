#pragma once
#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

using namespace physx;

class Floor {
private:
	PxRigidStatic* rb;
	RenderItem* item;
	PxTransform* position;

public:
	Floor(Vector3 pos, PxScene* gScene) : position(new PxTransform(pos)) {
		rb = PxGetPhysics().createRigidStatic(*position);

		auto geometry = PxBoxGeometry(99999, 1, 99999);
		auto shape = CreateShape(geometry);

		rb->attachShape(*shape);
		gScene->addActor(*rb);
		item = new RenderItem(shape, rb, Vector4(0, 1, 0, 0));
	}

	~Floor() { DeregisterRenderItem(item); item = nullptr; position = nullptr; }

	inline void setPos(Vector3 new_pos) { position->p = new_pos; }
	inline Vector3 getPos() { return position->p; }
};

