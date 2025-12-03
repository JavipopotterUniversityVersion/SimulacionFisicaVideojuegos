#include "Spring.h"
#include <iostream>

void Spring::integrate(double t) {
	if (attached_particle == nullptr) {
		std::cout << "NO ATTACHED PARTICLE TO SPRING" << std::endl;
	}

	Vector3 base_pos = pos;
	if (base_particle != nullptr) base_pos = base_particle->getPos();

	const Vector3 diff = pos - attached_particle->getPos();

	const float distance = diff.magnitude();
	const float delta = distance - spring_lenght;

	const Vector3 force = diff * delta * K;
	attached_particle->addForce(Vector3(0, -9.8, 0));

	attached_particle->addForce(force);
	attached_particle->Integrate(t);
}
