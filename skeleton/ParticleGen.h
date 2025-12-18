#pragma once
#include <random>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "DynamicParticle.h"

class Particle;

class ParticleGen
{
protected:
	Vector3 pos;
	std::uint32_t rate;
	double dur;

	Vector4 gradient_start;
	Vector4 gradient_end;

	double position_variation = 10;
	double speed = 10;
	bool enabled = true;
public:
	ParticleGen(Vector3 pos, double dur, std::uint32_t rate, 
		double speed = 10, double position_variation = 10, Vector4 g_start = Vector4(1,1,1,1), Vector4 g_end = Vector4(0, 0, 0, 0))
		: pos(pos), dur(dur), rate(rate), position_variation(position_variation), speed(speed), gradient_start(g_start), gradient_end(g_end) {};

	virtual std::vector<Particle*> GenerateP() = 0;
	virtual std::vector<DynamicParticle*> GenerateDP(PxPhysics* gPhysics, PxScene* gScene) = 0;
	std::mt19937 _mt;

	inline Vector3 getPos() { return pos; };
	inline double getDur() { return dur; };

	void setPosition(Vector3 position) { pos = position; }
	void setGradients(Vector4 st, Vector4 end) {
		gradient_start = st;
		gradient_end = end;
	}

	void Enable() { enabled = true; }
	void Disable() { enabled = false; }
};