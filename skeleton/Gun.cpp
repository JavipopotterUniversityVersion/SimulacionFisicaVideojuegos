#include "Gun.h"
#include <iostream>
#include <random>

void
Gun::Update(double t) {
	int size = bullets.size();

	for (int i = 0; i < size; ++i) {
		auto aux = bullets.front();
		bullets.pop();

		if (aux->hasToDie()) {
			delete aux;
			aux = nullptr;
		}
		else {
			aux->Integrate(t);
			bullets.push(aux);
		}
	}
}

void
Gun::Shoot() {
	auto part = new Particle(iPos, simulatedVelocity, acceleration, lifeTime, damping, mode);
	bullets.push(part);
}

double
Gun::SetSimulatedSpeed(double simulatedVel) {

	auto direction = rDirection.getNormalized();
	simulatedVelocity = Vector3(direction * simulatedVel);

	double realSpeed = rDirection.magnitude();
	simulatedMass = Rmass * pow(realSpeed / simulatedVel, 2);

	return simulatedMass;
}

void Gun::SetRotation(PxQuat q) {
	PxVec3 dir = q.rotate({ 0,0,-rDirection.magnitude()});
	rDirection = dir;
	//rDirection = PxVec3(rand(), rand(), rand());
	SetSimulatedSpeed(20);
}