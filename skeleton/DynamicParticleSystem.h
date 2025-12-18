#pragma once
#include <list>
#include "DynamicParticle.h"
#include "ParticleGen.h"
#include "ForceGenerator.h"

class DynamicParticleSystem
{
	Vector3 pos;
	double lifeTime;
	bool enabled = true;

	std::vector<ParticleGen*> particle_generators;
	std::vector<ForceGenerator*> force_generators;

	std::list<DynamicParticle*> particles;
	physx::PxPhysics* gPhysics;
	physx::PxScene* gScene;
public:
	DynamicParticleSystem(Vector3 P, std::vector<ParticleGen*> particle_generators, std::vector<ForceGenerator*> force_generators) : pos(P), particle_generators(particle_generators), force_generators(force_generators) {
		particles = std::list<DynamicParticle*>();
	};

	~DynamicParticleSystem() {
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

	inline void SetPosition(Vector3 newPos) { pos = newPos; };
	void Update(double t);

	void Enable() {enabled = true;}
	void Disable() { enabled = false; }
};

