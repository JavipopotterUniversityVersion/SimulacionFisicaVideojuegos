#include "Particle.h"
#include <iostream>

void
Particle::Integrate(double t) {


	switch (mode) {
	case(Mode::EULER):
		lastPosition = position->p;
		position->p = position->p + t * velocity;
		velocity = velocity + t * acceleration;
		velocity = velocity * pow(damping, t);
		break;
	case(Mode::SI_EULER):
		lastPosition = position->p;
		velocity = velocity + t * acceleration;
		position->p = position->p + t * velocity;
		velocity = velocity * pow(damping, t);
		break;
	case(Mode::VERLET):
		lastPosition = position->p;
		position->p = position->p + t * velocity;
		velocity = velocity + t * acceleration;
		velocity = velocity * pow(damping, t);
		mode = Mode::POST_VERLET;
		break;
	case(Mode::POST_VERLET):
		auto nPos = 2 * position->p - lastPosition + pow(t, 2)*acceleration;
		lastPosition = position->p;
		position->p = nPos;
		break;
	}

	lifeTime -= t;
	//std::cout << tVida << "\n";
}