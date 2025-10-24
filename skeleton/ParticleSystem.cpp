#include "ParticleSystem.h"

void
ParticleSystem::Update(double t) {
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

	for (auto generator : generators) {
		std::vector<Particle*> new_particles = generator->GenerateP();
		particles.insert(particles.end(), new_particles.begin(), new_particles.end());
	}
}