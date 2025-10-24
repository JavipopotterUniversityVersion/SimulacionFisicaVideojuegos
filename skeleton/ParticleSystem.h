#pragma once
#include <list>
#include "Particle.h"
#include "ParticleGen.h"

class ParticleSystem
{
	Vector3 iPos;
	double lifeTime; // in seconds
	Particle::Mode mode;
	std::vector<ParticleGen*> generators;

	std::list<Particle*> particles;

public:
	ParticleSystem(Vector3 P, std::vector<ParticleGen*> generators) : iPos(P), generators(generators){
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
		for (int i = 0; i < generators.size(); ++i) {
			delete generators[i];
		}
	}

	inline void SetPosition(PxVec3 newPos) { iPos = newPos; };
	void Update(double t);
};

