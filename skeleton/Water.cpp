#include "Water.h"
#include <PxPhysicsAPI.h>

Water::Water(Vector3 pos, Vector3 halfExtents) {
    physx::PxVec3 adjustedPos = physx::PxVec3(pos.x, pos.y + halfExtents.y, pos.z);
    position = new physx::PxTransform(adjustedPos);

    auto geometry = physx::PxBoxGeometry(halfExtents);
    auto shape = CreateShape(geometry);

    item = new RenderItem(shape, position, Vector4(0, 0, 1, 0));
}


void Water::addTarget(physx::PxRigidDynamic* target) {
	targets.push_back(target);
}

void Water::integrate(float t) {
	for (auto target : targets) {
        if (isInside(target)) {
            float h = target->getGlobalPose().p.y;

            physx::PxShape* shape = item->shape;
            physx::PxBoxGeometry box;

            if (!shape || !shape->getBoxGeometry(box)) return;

            physx::PxTransform waterPose = *position;
            float h0 = waterPose.p.y;
            float _height = box.halfExtents.y * 2.0f;

            float immersed = 0.0f;

            if (h - h0 > _height * 0.5f) {
                immersed = 0.0f;
            }
            else if (h0 - h > _height * 0.5f) {
                immersed = 1.0f;
            }
            else {
                immersed = (h0 - h) / _height + 0.5f;
            }

            Vector3 f = Vector3(0, 1, 0) * LIQUID_DENSITY * immersed;
            target->addForce(f);
        }
	}
}

bool Water::isInside(physx::PxRigidDynamic* target) {
    physx::PxShape* shape = item->shape;
    physx::PxBoxGeometry box;

    if (!shape || !shape->getBoxGeometry(box)) return false;

    physx::PxTransform waterPose = *position;
    physx::PxVec3 halfExtents = box.halfExtents;

    physx::PxVec3 targetPos = target->getGlobalPose().p;
    physx::PxVec3 localPos = waterPose.transformInv(targetPos);

    return abs(localPos.x) <= halfExtents.x &&
        abs(localPos.y) <= halfExtents.y &&
        abs(localPos.z) <= halfExtents.z;
}
