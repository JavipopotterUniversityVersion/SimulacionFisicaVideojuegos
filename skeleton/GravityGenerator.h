#pragma once
#include "ForceGenerator.h"

class GravityGenerator : public ForceGenerator
{
protected:
	double _gravity_force;
public:
	GravityGenerator(Vector3 pos, double gravity_force) : ForceGenerator(pos), _gravity_force(gravity_force) {}
	~GravityGenerator() {}
	void ApplyForce(const std::list<Particle*>& particles, double t) override;
};

