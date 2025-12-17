#include "DynamicParticleCannon.h"
#include <iostream>
#include <random>

void DynamicParticleCannon::Update(double t) {
	int size = particles.size();

	for (int i = 0; i < size; ++i) {
		auto aux = particles.front();
		particles.pop();

		if (aux->hasToDie()) {
			delete aux;
			aux = nullptr;
		}
		else {
			aux->Update(t);
			particles.push(aux);
		}
	}

	if (target != nullptr) {
		PxVec3 targetPos = target->getGlobalPose().p;
		PxVec3 dir = targetPos - pos;
		dir.normalize();

		rDirection = dir;
	}

	timer += t;
	if (timer >= SHOOT_RATE) {
		timer = 0;
		Shoot();
	}
}

void DynamicParticleCannon::Shoot() {
	auto part = new DynamicParticle(gPhysics, gScene, pos, 0.1f, 1);
	part->addForce(rDirection * CANNON_FORCE);
	particles.push(part);
}

void DynamicParticleCannon::SetRotation(PxQuat q) {
	PxVec3 dir = q.rotate({ 0,0,-rDirection.magnitude() });
	rDirection = dir;
}