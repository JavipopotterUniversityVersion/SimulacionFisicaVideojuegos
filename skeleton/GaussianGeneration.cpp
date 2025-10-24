#include "GaussianGeneration.h"
#include "Particle.h"

std::vector<Particle*> GaussianGeneration::GenerateP() {
	std::vector<Particle*> particles;
	for (int i = 0; i < rate; ++i) {
		Vector3 direction = Vector3(_d(_mt), _d(_mt), _d(_mt));
		direction = direction.getNormalized();
		Vector3 position = pos + direction * position_variation;
		particles.push_back(new Particle(position, direction * speed, {0,0,0}, dur, 1, Particle::SI_EULER));
	}
	return particles;
}
