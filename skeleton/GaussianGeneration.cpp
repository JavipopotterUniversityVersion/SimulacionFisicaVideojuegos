#include "GaussianGeneration.h"
#include "Particle.h"
#include "DynamicParticle.h"

std::vector<Particle*> GaussianGeneration::GenerateP() {
	if (!enabled) return std::vector<Particle*>();

	std::vector<Particle*> particles;
	for (int i = 0; i < rate; ++i) {
		Vector3 direction = Vector3(_d(_mt), _d(_mt), _d(_mt));
		direction = direction.getNormalized();
		Vector3 position = pos + direction * position_variation;

		float t = 0.5f * (_d(_mt) + 1.0f);
		Vector4 color = gradient_start * (1.0f - t) + gradient_end * t;

		particles.push_back(new Particle(position, direction * speed, {0,0,0}, dur, 1.0, 1.0, Particle::SI_EULER, color));
	}
	return particles;
}

std::vector<DynamicParticle*> GaussianGeneration::GenerateDP() {
	if (!enabled) return std::vector<DynamicParticle*>();

	std::vector<DynamicParticle*> particles;
	for (int i = 0; i < rate; ++i) {
		Vector3 direction = Vector3(_d(_mt), _d(_mt), _d(_mt));
		direction = direction.getNormalized();
		Vector3 position = pos + direction * position_variation;

		float t = 0.5f * (_d(_mt) + 1.0f);
		Vector4 color = gradient_start * (1.0f - t) + gradient_end * t;

		particles.push_back(new DynamicParticle());
	}
	return particles;
}
