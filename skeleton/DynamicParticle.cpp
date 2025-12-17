#include "DynamicParticle.h"

void DynamicParticle::Update(float t) {
	if (dead) return;

	timer += t;
	if (timer >= life_time) {
		dead = true;
	}
}