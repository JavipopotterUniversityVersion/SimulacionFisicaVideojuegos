#pragma once
#include "ParticleGen.h"
class UniformGeneration : public ParticleGen
{
protected:
	std::uniform_real_distribution<double> _d{ 0,1 };
public:
	UniformGeneration(Vector3 pos, Vector3 vel, double dur, std::uint32_t rate = 10, double speed = 10, float pos_var = 10) : ParticleGen(pos, vel, dur, rate, speed, pos_var) {};
	virtual std::vector<Particle*> GenerateP() override;
};

