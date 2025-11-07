#include "Player.h"

void Player::Move(Vector3 m) {
	dir = m;
}

void Player::Update(double t) {
	Vector3 forceToAdd = dir * SPEED;
	if (dir == -last_dir) {
		last_dir = dir;
		dir = Vector3(0, 0, 0);
		forceToAdd = -body->getForce();
	}
	body->addForce(forceToAdd);
	body->Integrate(t);
}