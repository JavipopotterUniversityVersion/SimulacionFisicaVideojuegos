#pragma once
#include <PxPhysicsAPI.h>
#include <cmath>
#include "ParticleSystem.h"

class ParabolicMover {
private:
    ParticleSystem* ps = nullptr;

    PxVec3 start;
    PxVec3 target;
    PxVec3 pos;
    PxVec3 vel;

    float gravity = -9.81f;
    float elapsed = 0.0f;
    float timeToHit = 1.0f;
    const float RESET_DELAY = 1.0f;
    bool finished = false;

public:
    ParabolicMover(ParticleSystem* system,
        const PxVec3& startPos,
        const PxVec3& targetPos,
        float tHit = 2.0f)
        : ps(system), start(startPos), target(targetPos), pos(startPos), timeToHit(tHit)
    {
        if (ps) ps->SetPosition(startPos);

        float T = tHit;
        float vx = (targetPos.x - startPos.x) / T;
        float vz = (targetPos.z - startPos.z) / T;
        float vy = (targetPos.y - startPos.y - 0.5f * gravity * T * T) / T;

        vel = PxVec3(vx, vy, vz);
    }
    
    void Reset(Vector3 new_target);
    void Update(float dt);

    bool IsFinished() const { return finished; }
};
