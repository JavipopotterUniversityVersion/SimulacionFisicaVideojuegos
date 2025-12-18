#include "Diego.h"
#include "RenderUtils.hpp"

using namespace physx;

static PxMaterial* createDefaultMaterial(PxPhysics* gPhysics) {
    return gPhysics->createMaterial(0.5f, 0.5f, 0.6f);
}

static void setupCapsule(PxRigidDynamic*& body, PxTransform*& tr, PxPhysics* gPhysics, PxScene* gScene,
    const PxVec3& position, float radius, float halfHeight, PxMaterial* mat, Vector4 color, RenderItem*& renderItem)
{
    tr = new PxTransform(position);
    body = gPhysics->createRigidDynamic(*tr);
    body->createShape(PxCapsuleGeometry(radius, halfHeight), *mat);
    body->setMass(1.0f);
    gScene->addActor(*body);
    
    PxShape* shape = nullptr;
    body->getShapes(&shape, 1);
    renderItem = new RenderItem(shape, body, color);
}

static void setupBox(PxRigidDynamic*& body, PxTransform*& tr, PxPhysics* gPhysics, PxScene* gScene,
    const PxVec3& position, const PxVec3& halfExtents, PxMaterial* mat, Vector4 color, RenderItem*& renderItem)
{
    tr = new PxTransform(position);
    body = gPhysics->createRigidDynamic(*tr);
    body->createShape(PxBoxGeometry(halfExtents), *mat);
    body->setMass(2.0f);
    gScene->addActor(*body);

    PxShape* shape = nullptr;
    body->getShapes(&shape, 1);
    renderItem = new RenderItem(shape, body, color);
}

static void setupSphere(PxRigidDynamic*& body, PxTransform*& tr, PxPhysics* gPhysics, PxScene* gScene,
    const PxVec3& position, float radius, PxMaterial* mat, Vector4 color, RenderItem*& renderItem)
{
    tr = new PxTransform(position);
    body = gPhysics->createRigidDynamic(*tr);
    body->createShape(PxSphereGeometry(radius), *mat);
    body->setMass(1.0f);
    gScene->addActor(*body);

    PxShape* shape = nullptr;
    body->getShapes(&shape, 1);
    renderItem = new RenderItem(shape, body, color);
}

static PxSphericalJoint* connect(PxPhysics* gPhysics,
    PxRigidActor* a, const PxTransform& localA,
    PxRigidActor* b, const PxTransform& localB,
    float coneAngle = PxPi / 4)
{
    PxSphericalJoint* joint = PxSphericalJointCreate(*gPhysics, a, localA, b, localB);
    joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION, true);
    joint->setLimitCone(PxJointLimitCone(coneAngle, coneAngle, 0.01f));
    joint->setSphericalJointFlag(PxSphericalJointFlag::eLIMIT_ENABLED, true);
    return joint;
}

Diego::Diego(PxPhysics* gPhysics, PxScene* gScene, Vector3 pos, Vector4 color, float move_force, float break_factor)
{
    this->move_force = move_force;
    scene = gScene; 
    PxMaterial* mat = createDefaultMaterial(gPhysics); 
    PxVec3 base = PxVec3(pos.x, pos.y, pos.z);

    setupSphere(head_rb, head_tr, gPhysics, gScene, base + PxVec3(0, 2.2f, 0), 0.25f, mat, Vector4(1, 0.7, 0.7, 1), head_item);
    setupBox(chest_rb, chest_tr, gPhysics, gScene, base + PxVec3(0, 1.5f, 0), PxVec3(0.4f, 0.6f, 0.2f), mat, color, chest_item);
    setupBox(pelvis_rb, pelvis_tr, gPhysics, gScene, base + PxVec3(0, 0.85f, 0), PxVec3(0.3f, 0.15f, 0.2f), mat, color, pelvis_item);

    setupCapsule(left_upper_arm_rb, left_upper_arm_tr, gPhysics, gScene, base + PxVec3(-0.7f, 1.5f, 0), 0.1f, 0.3f, mat, color, left_upper_arm_item);
    setupCapsule(left_forearm_rb, left_forearm_tr, gPhysics, gScene, base + PxVec3(-1.1f, 1.5f, 0), 0.08f, 0.3f, mat, color, left_forearm_item);
    setupCapsule(right_upper_arm_rb, right_upper_arm_tr, gPhysics, gScene, base + PxVec3(0.7f, 1.5f, 0), 0.1f, 0.3f, mat, color, right_upper_arm_item);
    setupCapsule(right_forearm_rb, right_forearm_tr, gPhysics, gScene, base + PxVec3(1.1f, 1.5f, 0), 0.08f, 0.3f, mat, color, right_forearm_item);

    setupBox(left_thigh_rb, left_thigh_tr, gPhysics, gScene, base + PxVec3(-0.4f, 0.5f, 0), PxVec3(0.12f, 0.4f, 0.12f), mat, color, left_thigh_item);
    setupBox(left_calf_rb, left_calf_tr, gPhysics, gScene, base + PxVec3(-0.4f, -0.3f, 0), PxVec3(0.1f, 0.4f, 0.1f), mat, color, left_calf_item);
    setupBox(right_thigh_rb, right_thigh_tr, gPhysics, gScene, base + PxVec3(0.4f, 0.5f, 0), PxVec3(0.12f, 0.4f, 0.12f), mat, color, right_thigh_item);
    setupBox(right_calf_rb, right_calf_tr, gPhysics, gScene, base + PxVec3(0.4f, -0.3f, 0), PxVec3(0.1f, 0.4f, 0.1f), mat, color, right_calf_item);

    neck_joint = connect(gPhysics, head_rb, PxTransform(PxVec3(0, -0.25f, 0)), chest_rb, PxTransform(PxVec3(0, 0.6f, 0)));
    neck_joint->setBreakForce(BREAK_FORCE_HEAD * break_factor, BREAK_TORQUE * break_factor);

    spine_joint = connect(gPhysics, chest_rb, PxTransform(PxVec3(0, -0.6f, 0)), pelvis_rb, PxTransform(PxVec3(0, 0.15f, 0)));
    spine_joint->setBreakForce(BREAK_FORCE_SPINE * break_factor, BREAK_TORQUE * break_factor);

    left_shoulder_joint = connect(gPhysics, left_upper_arm_rb, PxTransform(PxVec3(0.3f, 0, 0)), chest_rb, PxTransform(PxVec3(-0.4f, 0.4f, 0)));
    left_shoulder_joint->setBreakForce(BREAK_FORCE_ARM * break_factor, BREAK_TORQUE * break_factor);

    left_elbow_joint = connect(gPhysics, left_forearm_rb, PxTransform(PxVec3(0.3f, 0, 0)), left_upper_arm_rb, PxTransform(PxVec3(-0.3f, 0, 0)));
    left_elbow_joint->setBreakForce(BREAK_FORCE_ARM * break_factor, BREAK_TORQUE * break_factor);

    right_shoulder_joint = connect(gPhysics, right_upper_arm_rb, PxTransform(PxVec3(-0.3f, 0, 0)), chest_rb, PxTransform(PxVec3(0.4f, 0.4f, 0)));
    right_shoulder_joint->setBreakForce(BREAK_FORCE_ARM * break_factor, BREAK_TORQUE * break_factor);

    right_elbow_joint = connect(gPhysics, right_forearm_rb, PxTransform(PxVec3(-0.3f, 0, 0)), right_upper_arm_rb, PxTransform(PxVec3(0.3f, 0, 0)));
    right_elbow_joint->setBreakForce(BREAK_FORCE_ARM * break_factor, BREAK_TORQUE * break_factor);

    left_hip_joint = connect(gPhysics, left_thigh_rb, PxTransform(PxVec3(0.0f, 0.4f, 0)), pelvis_rb, PxTransform(PxVec3(-0.3f, -0.15f, 0)));
    left_hip_joint->setBreakForce(BREAK_FORCE_LEG * break_factor, BREAK_TORQUE * break_factor);

    left_knee_joint = connect(gPhysics, left_calf_rb, PxTransform(PxVec3(0.0f, 0.4f, 0)), left_thigh_rb, PxTransform(PxVec3(0.0f, -0.4f, 0)));
    left_knee_joint->setBreakForce(BREAK_FORCE_LEG * break_factor, BREAK_TORQUE * break_factor);

    right_hip_joint = connect(gPhysics, right_thigh_rb, PxTransform(PxVec3(0.0f, 0.4f, 0)), pelvis_rb, PxTransform(PxVec3(0.3f, -0.15f, 0)));
    right_hip_joint->setBreakForce(BREAK_FORCE_LEG * break_factor, BREAK_TORQUE * break_factor);

    right_knee_joint = connect(gPhysics, right_calf_rb, PxTransform(PxVec3(0.0f, 0.4f, 0)), right_thigh_rb, PxTransform(PxVec3(0.0f, -0.4f, 0)));
    right_knee_joint->setBreakForce(BREAK_FORCE_LEG * break_factor, BREAK_TORQUE * break_factor);
}

static void applyUprightTorque(physx::PxRigidDynamic* body, float strength = 100.0f, physx::PxVec3 localAxisToAlign = physx::PxVec3(0, 1, 0))
{
    if (!body) return;

    physx::PxQuat current = body->getGlobalPose().q;

    physx::PxVec3 localDir = current.rotate(localAxisToAlign);

    physx::PxVec3 targetDir = physx::PxVec3(0, 1, 0);

    physx::PxVec3 axis = localDir.cross(targetDir);
    
    float dot = localDir.dot(targetDir);
    float angle = acosf(physx::PxClamp(dot, -1.0f, 1.0f));

    if (angle < 1e-4f || axis.normalize() < 1e-4f)
        return;

    physx::PxVec3 torque = axis * angle * strength;
    body->addTorque(torque, physx::PxForceMode::eACCELERATION);
}


void Diego::integrate(double delta) {
    if (play_dead) return;
    applyUprightTorque(pelvis_rb, 500.0f);
    applyUprightTorque(chest_rb, 500.0f);
    applyUprightTorque(head_rb, 500.0f);

    applyUprightTorque(left_thigh_rb, 500.0f);
    applyUprightTorque(right_thigh_rb, 500.0f);
    applyUprightTorque(left_calf_rb, 500.0f);
    applyUprightTorque(right_calf_rb, 500.0f);
}

void Diego::move(const physx::PxVec3& dir) {
    physx::PxVec3 normalized = dir.getNormalized();
    physx::PxVec3 velocity = pelvis_rb->getLinearVelocity();

    physx::PxVec3 horizontalVel = physx::PxVec3(velocity.x, 0, velocity.z);
    float currentSpeed = horizontalVel.magnitude();

    if (currentSpeed < max_speed) {
        pelvis_rb->addForce(normalized * move_force, physx::PxForceMode::eACCELERATION);
    }
}

bool Diego::isGrounded()
{
    physx::PxVec3 origin = pelvis_rb->getGlobalPose().p - Vector3(0, 1, 0);
    physx::PxVec3 direction = physx::PxVec3(0, -1, 0);
    float maxDistance = 3.0f;
    physx::PxRaycastBuffer hit;

    bool hasHit = scene->raycast(origin, direction, maxDistance, hit,
        physx::PxHitFlag::eDEFAULT,
        physx::PxQueryFilterData(physx::PxQueryFlag::eSTATIC | physx::PxQueryFlag::eDYNAMIC));

    return hasHit;
}

bool Diego::isWalled() {
    physx::PxVec3 origin = chest_rb->getGlobalPose().p + Vector3(0, 0, 1);
    physx::PxVec3 direction = physx::PxVec3(0, 0, 1);
    float maxDistance = 0.6f;
    physx::PxRaycastBuffer hit;

    bool hasHit = scene->raycast(origin, direction, maxDistance, hit,
        physx::PxHitFlag::eDEFAULT,
        physx::PxQueryFilterData(physx::PxQueryFlag::eSTATIC | physx::PxQueryFlag::eDYNAMIC));

    return hasHit;
}


void Diego::jump()
{
    if (!isGrounded() && !isWalled()) return;
    pelvis_rb->addForce(physx::PxVec3(0, JUMP_FORCE, 0), physx::PxForceMode::eIMPULSE);
}


Diego::~Diego()
{
}

void Diego::resetPose(Vector3 pos)
{
}

void Diego::stop() {
    pelvis_rb->setLinearVelocity(physx::PxVec3(0));
    pelvis_rb->setAngularVelocity(physx::PxVec3(0));
    pelvis_rb->clearForce(physx::PxForceMode::eFORCE);
    pelvis_rb->clearTorque(physx::PxForceMode::eFORCE);
}

void Diego::kill() {
    left_elbow_joint->release();
    left_hip_joint->release();
    right_elbow_joint->release();
    right_hip_joint->release();
    neck_joint->release();
    spine_joint->release();
    left_shoulder_joint->release();
    right_shoulder_joint->release();
    left_elbow_joint->release();
    right_elbow_joint->release();
}