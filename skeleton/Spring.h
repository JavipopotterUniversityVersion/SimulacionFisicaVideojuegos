#pragma once
#include "vector"
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "Particle.h"

class Spring
{
private:
	float spring_lenght;
	float K;
	Vector3 pos;
	Particle* base_particle = nullptr;
	Particle* attached_particle;
public:
	Spring(Vector3 pos, Particle* att = nullptr, float k = 1, float l = 10) : 
		pos(pos), attached_particle(att), K(k), spring_lenght(l), base_particle(nullptr) {}

	void integrate(double t);
	void const setAttachedParticle(Particle* att) { attached_particle = att; };
	void const setBaseParticle(Particle* att) { base_particle = att; };
};

