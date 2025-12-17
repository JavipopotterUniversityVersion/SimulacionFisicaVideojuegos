#pragma once

#include <PxPhysicsAPI.h>
#include "core.hpp"

using namespace physx;

class RenderItem;

class Diego
{
private:
    const float MOVE_FORCE = 1000.0f;
    const float JUMP_FORCE = 100.0f;

    //Rb an TR
    PxTransform* head_tr = nullptr;
    PxRigidDynamic* head_rb = nullptr;

    PxTransform* chest_tr = nullptr;
    PxRigidDynamic* chest_rb = nullptr;

    PxTransform* pelvis_tr = nullptr;
    PxRigidDynamic* pelvis_rb = nullptr;

    PxTransform* left_upper_arm_tr = nullptr;
    PxRigidDynamic* left_upper_arm_rb = nullptr;

    PxTransform* left_forearm_tr = nullptr;
    PxRigidDynamic* left_forearm_rb = nullptr;

    PxTransform* right_upper_arm_tr = nullptr;
    PxRigidDynamic* right_upper_arm_rb = nullptr;

    PxTransform* right_forearm_tr = nullptr;
    PxRigidDynamic* right_forearm_rb = nullptr;

    PxTransform* left_thigh_tr = nullptr;
    PxRigidDynamic* left_thigh_rb = nullptr;

    PxTransform* left_calf_tr = nullptr;
    PxRigidDynamic* left_calf_rb = nullptr;

    PxTransform* right_thigh_tr = nullptr;
    PxRigidDynamic* right_thigh_rb = nullptr;

    PxTransform* right_calf_tr = nullptr;
    PxRigidDynamic* right_calf_rb = nullptr;

    // Joints
    PxSphericalJoint* neck_joint = nullptr;

    PxSphericalJoint* left_shoulder_joint = nullptr;
    PxSphericalJoint* left_elbow_joint = nullptr;

    PxSphericalJoint* right_shoulder_joint = nullptr;
    PxSphericalJoint* right_elbow_joint = nullptr;

    PxSphericalJoint* spine_joint = nullptr;

    PxSphericalJoint* left_hip_joint = nullptr;
    PxSphericalJoint* left_knee_joint = nullptr;

    PxSphericalJoint* right_hip_joint = nullptr;
    PxSphericalJoint* right_knee_joint = nullptr;

    // Render Items
    RenderItem* head_item = nullptr;
    RenderItem* chest_item = nullptr;
    RenderItem* pelvis_item = nullptr;

    RenderItem* left_upper_arm_item = nullptr;
    RenderItem* left_forearm_item = nullptr;
    RenderItem* right_upper_arm_item = nullptr;
    RenderItem* right_forearm_item = nullptr;

    RenderItem* left_thigh_item = nullptr;
    RenderItem* left_calf_item = nullptr;
    RenderItem* right_thigh_item = nullptr;
    RenderItem* right_calf_item = nullptr;

    //Other
    PxScene* scene = nullptr;
public:
    Diego(PxPhysics* gPhysics, PxScene* gScene, Vector3 pos);
    ~Diego();

    inline PxRigidDynamic* getChest() const { return chest_rb; }
    inline PxRigidDynamic* getPelvis() const { return pelvis_rb; }

    void resetPose(Vector3 pos);
    void addToScene(PxScene* gScene);
    void removeFromScene(PxScene* gScene);

    void integrate(double delta);
    void move(const physx::PxVec3& dir);

    void jump();
    bool isGrounded();
};
