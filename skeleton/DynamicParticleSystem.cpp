#include "DynamicParticleSystem.h"
#include <iostream>

void
DynamicParticleSystem::Update(double t) {
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
			particles.push_back(aux);
			aux->Update(t);
		}
	}

	for (auto generator : particle_generators) {
		std::vector<DynamicParticle*> new_particles = generator->GenerateDP(gPhysics, gScene);
		generator->setPosition(pos);
		particles.insert(particles.end(), new_particles.begin(), new_particles.end());
	}

	for (auto generator : force_generators) {
		generator->ApplyForce(particles, t);
		generator->setPos(pos);
	}
}