#pragma once

#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "RenderUtils.hpp"

using namespace physx;

class DynamicParticle {
protected:
    PxRigidDynamic* body = nullptr;
    RenderItem* item = nullptr;

    Vector4 color;
    float radius;

public:
    DynamicParticle(PxPhysics* gPhysics, PxScene* gScene, Vector3 pos, float mass = 1.0f, float radius = 0.5f, Vector4 color = { 1, 0, 0, 1 })
        : radius(radius), color(color)
    {
        PxTransform t(pos);
        body = gPhysics->createRigidDynamic(t);

        PxSphereGeometry geometry(radius);
        PxMaterial* mat = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

        PxShape* shape = body->createShape(geometry, *mat);
        body->setMass(mass);
        gScene->addActor(*body);

        item = new RenderItem(shape, body, color);
    }

    ~DynamicParticle() {
        DeregisterRenderItem(item);
        body->release();
    }

    void addForce(const PxVec3& force, PxForceMode::Enum mode = PxForceMode::eACCELERATION) {
         body->addForce(force, mode);
    }

    PxRigidDynamic* getBody() const { return body; }
    inline Vector3 getPos() const { return body->getGlobalPose().p; }
    Vector3 getVelocity() const {return body->getLinearVelocity();}

    void setVelocity(const PxVec3& vel) {body->setLinearVelocity(vel);}

    void clearForces() { body->clearForce(); }
};
