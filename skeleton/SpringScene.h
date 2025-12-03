#pragma once
#include "Scene.h"
#include "Spring.h"
#include "Diego.h"
#include "Floor.h"

class SpringScene : public Scene
{
private:
	Spring* mSpring;
	Diego* diego;
	Floor* floor;
public:
	SpringScene(PxPhysics* gPhysics, PxMaterial* gMaterial, PxScene* gScene) : Scene(gPhysics, gMaterial, gScene) {};
	virtual void integrate(double t) override;
	virtual void init() override;
	virtual void keyPress(unsigned char key, const physx::PxTransform& camera) override;
	~SpringScene();
};

