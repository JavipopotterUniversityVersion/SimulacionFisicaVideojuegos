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
	RenderItem* item;
	PxTransform* position;

public:
	Floor(Vector3 pos) : position(new PxTransform(pos)) {
		auto geometry = PxBoxGeometry(99999, 1, 99999);
		auto shape = CreateShape(geometry);
		item = new RenderItem(shape, position, Vector4(0, 1, 0, 0));
	}

	~Floor() { DeregisterRenderItem(item); item = nullptr; position = nullptr; }

	inline void setPos(Vector3 new_pos) { position->p = new_pos; }
	inline Vector3 getPos() { return position->p; }
};

