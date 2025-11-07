#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGen.h"
#include "ForceGenerator.h"

class ParticleSystem
{
	Vector3 pos;
	double lifeTime; // in seconds
	Particle::Mode mode;
	std::vector<ParticleGen*> particle_generators;
	std::vector<ForceGenerator*> force_generators;
	bool enabled = true;

	std::list<Particle*> particles;

public:
	ParticleSystem(Vector3 P, std::vector<ParticleGen*> particle_generators, std::vector<ForceGenerator*> force_generators) : pos(P), particle_generators(particle_generators), force_generators(force_generators){
		particles = std::list<Particle*>();
	};

	~ParticleSystem() { 
		int size = particles.size(); 
		for (int i = 0; i < size; ++i) { 
			auto aux = particles.front(); 
			particles.pop_front(); 
			delete aux; 
			aux = nullptr; 
		}
		for (int i = 0; i < particle_generators.size(); ++i) {
			delete particle_generators[i];
		}
		for (int i = 0; i < force_generators.size(); ++i) {
			delete force_generators[i];
		}
	}

	inline void SetPosition(PxVec3 newPos) { pos = newPos; };
	void Update(double t);

	void HandleForce(int index, bool enable = true) {
		if (enable) force_generators[index]->Enable();
		else force_generators[index]->Disable();
	}

	void HandleGenerator(int index, bool enable = true) {
		if (enable) particle_generators[index]->Enable();
		else particle_generators[index]->Disable();
	}

	void Enable() { 
		for (auto force : force_generators) force->Enable();
		enabled = true; 
	}
	void Disable() { enabled = false; }
};

