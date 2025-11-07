#pragma once
#include "Particle.h"
using namespace physx;

class Player {
private:
	Particle* body;
	const float SPEED = 100.0f;
	Vector3 dir;
	Vector3 last_dir;

public:
	Player(Particle* p) : body(p), dir(Vector3(0,0,0)) {
	}

	void Move(Vector3 m);
	void Update(double t);

	inline Vector3 getPos() { return body->getPos(); }
};

