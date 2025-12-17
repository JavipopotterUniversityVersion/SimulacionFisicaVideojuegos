#pragma once
#include "Diego.h"

class Marco
{
private:
	Diego* diego;
	PxRigidDynamic* target;

	float timer = 0;
	float target_time = 0;
	bool moving = true;
public:
	void integrate(float t);
	void setTarget(PxRigidDynamic* t) { target = t; }

	Marco(PxPhysics* gPhysics, PxScene* gScene, Vector3 pos, Vector4 color = { 1,1,1,1 }, float move_force = 250.0f);
	~Marco() {
		delete diego;
	}

	inline Diego* getDiego() { return diego; }
};

