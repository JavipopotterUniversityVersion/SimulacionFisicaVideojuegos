#pragma once
#include "ForceGenerator.h"
class WindGenerator : public ForceGenerator
{
protected:
	Vector3 volume;
	Vector3 wind_velocity;

	float k1;
	float k2;

	bool IsPointInsideVolume(const Vector3& posToCheck);
public:
	WindGenerator(Vector3 pos, Vector3 volume, Vector3 wind_velocity, float k1 = 1.0, float k2 = 0.0): 
		ForceGenerator(pos), volume(volume), wind_velocity(wind_velocity), k1(k1), k2(k2) {}
	~WindGenerator() {}
	void ApplyForce(const std::list<Particle*>& particles, double t) override;
};

