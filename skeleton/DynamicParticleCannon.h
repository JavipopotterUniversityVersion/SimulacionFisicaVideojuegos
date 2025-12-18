#pragma once
#include <queue>
#include "DynamicParticle.h"

class DynamicParticleCannon
{
	float PARTICLE_MASS_MIN = 1.0f;
	float PARTICLE_MASS_MAX = 3.0f;

	const float CANNON_FORCE = 4000.0f;
	Vector3 pos;
	Vector3 rDirection;

	std::queue<DynamicParticle*> particles;
	PxScene* gScene;
	PxPhysics* gPhysics;

	PxRigidDynamic* target;

	float timer = 0;
	const float SHOOT_RATE = 0.2f;
	bool enabled = true;
public:
	DynamicParticleCannon(Vector3 P, PxPhysics* gPhysics, PxScene* gScene) : pos(P), gScene(gScene), gPhysics(gPhysics) {
		particles = std::queue<DynamicParticle*>();
	};

	~DynamicParticleCannon() { int size = particles.size(); for (int i = 0; i < size; ++i) { auto aux = particles.front(); particles.pop(); delete aux; aux = nullptr; } }

	inline void SetPosition(PxVec3 newPos) { pos = newPos; };
	void SetRotation(PxQuat q);

	void Shoot();
	void Update(double t);

	void setTarget(PxRigidDynamic* t) { target = t; }
	void toggle() { enabled = !enabled; }
};

