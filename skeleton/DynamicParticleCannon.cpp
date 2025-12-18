#include "DynamicParticleCannon.h"
#include <iostream>
#include <random>
#include <ctime>

static float randomRange(float min, float max) {
	static std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
	std::uniform_real_distribution<float> dist(min, max);
	return dist(rng);
}

static float lerp(float a, float b, float t) {
	return (1.0f - t) * a + t * b;
}

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
		if(enabled) Shoot();
	}
}

void DynamicParticleCannon::Shoot() {
	float mass = randomRange(PARTICLE_MASS_MIN, PARTICLE_MASS_MAX);
	float radius = lerp(0.3f, 1.0f, mass / PARTICLE_MASS_MAX);
	auto part = new DynamicParticle(gPhysics, gScene, pos, 1.0f, 1, radius, Vector4(0,0,1,1));
	part->addForce(rDirection * CANNON_FORCE);
	particles.push(part);
}

void DynamicParticleCannon::SetRotation(PxQuat q) {
	PxVec3 dir = q.rotate({ 0,0,-rDirection.magnitude() });
	rDirection = dir;
}