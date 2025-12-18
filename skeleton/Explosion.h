#pragma once
#include "ForceGenerator.h"
class Explosion : public ForceGenerator
{
private:
	double radius;
	double time_constant;
	double force;
	double time;
public:
	Explosion(Vector3 pos, double r, double tC, double explosionForce);
	void ApplyForce(const std::list<Particle*>& particles, double t) override;
	void ApplyForce(const std::list<DynamicParticle*>& particles, double t) override;
	void Enable() override;
};

