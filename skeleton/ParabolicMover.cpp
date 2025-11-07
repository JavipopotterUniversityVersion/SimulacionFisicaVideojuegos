#include "ParabolicMover.h"
#include <iostream>

void ParabolicMover::Reset(Vector3 new_target) {
    finished = false;
    elapsed = 0;
    target = new_target;

    float vx = (target.x - start.x) / timeToHit;
    float vz = (target.z - start.z) / timeToHit;
    float vy = (target.y - start.y - 0.5f * gravity * timeToHit * timeToHit) / timeToHit;

    vel = PxVec3(vx, vy, vz);
    pos = start;
}

void ParabolicMover::Update(float dt) {
    if (finished || ps == nullptr) return;

    elapsed += dt;

    vel.y += gravity * dt;

    pos += vel * dt;

    ps->SetPosition(pos);

    if (elapsed >= timeToHit) {
        ps->HandleForce(0, true);
        ps->HandleGenerator(0, false);
        ps->SetPosition(target);

        if (elapsed >= timeToHit + RESET_DELAY) {
            ps->SetPosition(start);
            pos = start;
            ps->HandleForce(0, false);
            ps->HandleGenerator(0, true);
            finished = true;
        }
    }

}