#include "GravityGenerator.h"
#include "Particle.h"

void GravityGenerator::ApplyForce(const std::list<Particle*>& particles, double t) {
	for (auto particle : particles) {
		particle->addForce(Vector3(0, -1, 0) * _gravity_force);
	}
}