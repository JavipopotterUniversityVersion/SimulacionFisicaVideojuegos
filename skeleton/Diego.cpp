#include "Diego.h"
#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

Diego::Diego(physx::PxPhysics* gPhysics, physx::PxScene* gScene, Vector3 pos) {
	diego_tr = new physx::PxTransform(pos);
	rb = gPhysics->createRigidDynamic(*diego_tr);

	auto geometry = physx::PxBoxGeometry(5, 5, 5);
	auto shape = CreateShape(geometry);

	rb->attachShape(*shape);
	gScene->addActor(*rb);
	item = new RenderItem(shape, rb, Vector4(1, 0, 0, 0));
}