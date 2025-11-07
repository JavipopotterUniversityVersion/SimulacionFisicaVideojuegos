#include "Explosion.h"
#include "Particle.h"
#include <iostream>

Explosion::Explosion(Vector3 pos, double r, double tC, double force) : 
	ForceGenerator(pos), radius(r), time_constant(tC), force(force), time(0)
{

}

void Explosion::ApplyForce(const std::list<Particle*>& particles, double t) {
	if (!enabled) return;

	time += t;
	for (auto particle : particles) {
		float r = (particle->getPos() - pos).magnitude();
		if (r < radius)
		{
			Vector3 res = particle->getPos() - pos;
			res *= (force / pow(r, 2));
			res *= pow(exp(1.0), -(time / time_constant));
			particle->addForce(res);
		}
	}

	if (time >= time_constant) {
		enabled = false;
		time = 0;
	}
}

void Explosion::Enable() {
	ForceGenerator::Enable();
	time = 0;
}