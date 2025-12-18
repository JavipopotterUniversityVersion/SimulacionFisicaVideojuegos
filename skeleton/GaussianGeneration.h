#pragma once
#include "ParticleGen.h"

class GaussianGeneration : public ParticleGen
{
	protected:
		std::normal_distribution<double> _d{ 0,1 };
	public:
		GaussianGeneration(Vector3 pos, double dur, std::uint32_t rate = 10, double speed = 10) : ParticleGen(pos, dur, rate, speed) {};
		std::vector<Particle*> GenerateP() override;
		std::vector<DynamicParticle*> GenerateDP(PxPhysics* gPhysics, PxScene* gScene) override;
};