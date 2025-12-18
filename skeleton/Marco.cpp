#include "Marco.h"
#include <random>
#include <ctime>

static float randomRange(float min, float max) {
	static std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
	std::uniform_real_distribution<float> dist(min, max);
	return dist(rng);
}

void Marco::integrate(float t) {
	diego->integrate(t);

	if (target != nullptr && moving) {
		PxVec3 targetPos = target->getGlobalPose().p;
		PxVec3 dir = targetPos - diego->getChest()->getGlobalPose().p;
		dir.normalize();

		if(diego->isGrounded()) diego->move(dir);
	}

	timer += t;
	if (timer >= target_time) {
		diego->stop();
		target_time = randomRange(1, 3);
		moving = !moving;
		timer = 0;
	}
}

Marco::Marco(PxPhysics* gPhysics, PxScene* gScene, Vector3 pos, Vector4 color, float move_force) {
	diego = new Diego(gPhysics, gScene, pos, color, move_force, 0.15f);
	diego->setMaxSpeed(5.0f);
	target_time = randomRange(1,3);
}