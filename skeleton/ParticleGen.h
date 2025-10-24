#pragma once
#include <random>
#include <PxPhysicsAPI.h>
#include "core.hpp"
class Particle;

class ParticleGen
{
protected:
	Vector3 pos;
	std::uint32_t rate;
	double dur;

	double position_variation = 10;
	double speed = 10;
public:
	ParticleGen(Vector3 pos, Vector3 vel, double dur, std::uint32_t rate, double speed = 10, double position_variation = 10) : pos(pos), dur(dur), rate(rate),
		position_variation(position_variation), speed(speed) {};

	virtual std::vector<Particle*> GenerateP() = 0;
	std::mt19937 _mt;

	inline Vector3 getPos() { return pos; };
	inline double getDur() { return dur; };
};