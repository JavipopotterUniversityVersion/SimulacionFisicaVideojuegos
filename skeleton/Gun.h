#pragma once
#include <queue>
#include "Particle.h"

class Gun
{
	Vector3 iPos;
	Vector3 rDirection;
	Vector3 acceleration;
	double Rmass;
	double lifeTime;
	double damping;
	Particle::Mode mode;
	Vector3 simulatedVelocity;
	double simulatedMass;

	std::queue<Particle*> particles;

public:
	Gun(Vector3 P, Vector3 V, Vector3 A, double T, double d, Particle::Mode mass, double M) 
		: iPos(P), rDirection(V), acceleration(A), Rmass(M), lifeTime(T), damping(d), mode(mass), simulatedVelocity(V), simulatedMass(M) {
		particles = std::queue<Particle*>();
	};

	~Gun() { int size = particles.size(); for (int i = 0; i < size; ++i) { auto aux = particles.front(); particles.pop(); delete aux; aux = nullptr; } }

	inline void SetPosition(PxVec3 newPos) { iPos = newPos; };
	void SetRotation(PxQuat q);
	void Shoot();
	void Update(double t);
	double SetSimulatedSpeed(double simulatedVel);
};

