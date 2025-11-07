#include "Particle.h"
#include <iostream>

void
Particle::Integrate(double t) {

	auto l = force;
	a = force * invM;

	switch (mode) {
	case(Mode::EULER):
		lasPos = pos->p;
		pos->p = pos->p + t * v;
		v = v + t * a;
		v = v * pow(damping, t);
		break;
	case(Mode::SI_EULER):
		lasPos = pos->p;
		v = v + t * a;
		pos->p = pos->p + t * v;
		v = v * pow(damping, t);
		break;
	case(Mode::VERLET):
		lasPos = pos->p;
		pos->p = pos->p + t * v;
		v = v + t * a;
		v = v * pow(damping, t);
		mode = Mode::POST_VERLET;
		break;
	case(Mode::POST_VERLET):
		auto nPos = 2 * pos->p - lasPos + pow(t, 2) * a;
		lasPos = pos->p;
		pos->p = nPos;
		break;
	}
	clearForce();

	// If the time left is less than zero before the sustraction, the particle isn't destroyed
	if (tVida >= 0) {
		tVida -= t;
		if (tVida <= 0.0) dead = true;
	}

	return;
}

double
Particle::SetSimulatedVel(double simulatedVel) {

	auto direction = v.normalize();
	double realVel = v.magnitude();

	v = Vector3(direction * simulatedVel);
	auto simMass = pow(invM, -1) * pow(realVel / simulatedVel, 2);
	invM = pow(simMass, -1);

	return simMass;
}