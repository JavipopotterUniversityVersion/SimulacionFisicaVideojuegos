#include "SpringScene.h"

void SpringScene::init() {
	Particle* p = new Particle();
	mSpring = new Spring(Vector3(0,0,0), p, 2.0f, 20.0f);
	floor = new Floor(Vector3(0, 0, 0), gScene);
	diego = new Diego(gPhysics, gScene, Vector3(0,20,0));
}

void SpringScene::integrate(double t) {
	mSpring->integrate(t);
}

void SpringScene::keyPress(unsigned char key, const physx::PxTransform& camera) {
}

SpringScene::~SpringScene() {
	delete diego;
}
