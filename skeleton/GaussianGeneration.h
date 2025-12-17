#pragma once
#include "ParticleGen.h"

class GaussianGeneration : public ParticleGen
{
	protected:
		std::normal_distribution<double> _d{ 0,1 };
	public:
		GaussianGeneration(Vector3 pos, Vector3 vel, double dur, std::uint32_t rate = 10, double speed = 10) : ParticleGen(pos, vel, dur, rate, speed) {};
		virtual std::vector<Particle*> GenerateP() override;
		virtual std::vector<DynamicParticle*> GenerateDP() override;
};