#include "ParticleSystem.h"
#include <iostream>

void
ParticleSystem::Update(double t) {
	if (!enabled) return;
	int size = particles.size();

	for (int i = 0; i < size; ++i) {
		auto aux = particles.front();
		particles.pop_front();

		if (aux->hasToDie()) {
			delete aux;
			aux = nullptr;
		}
		else {
			aux->Integrate(t);
			particles.push_back(aux);
		}
	}

	for (auto generator : particle_generators) {
		std::vector<Particle*> new_particles = generator->GenerateP();
		generator->setPosition(pos);
		particles.insert(particles.end(), new_particles.begin(), new_particles.end());
	}

	for (auto generator : force_generators) {
		generator->ApplyForce(particles, t);
		generator->setPos(pos);
	}
}