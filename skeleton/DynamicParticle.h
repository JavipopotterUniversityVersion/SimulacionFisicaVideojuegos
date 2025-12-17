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

    bool dead = false;
    float life_time;
    float timer = 0;

public:
    DynamicParticle(PxPhysics* gPhysics, PxScene* gScene, Vector3 pos, float life_time = 5.0f, float mass = 0.1f, float radius = 0.5f, Vector4 color = { 1, 0, 0, 1 }, std::string geom = "")
        : radius(radius), color(color), life_time(life_time)
    {
        PxTransform t(pos);
        body = gPhysics->createRigidDynamic(t);

        PxMaterial* mat = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

        if (geom == "cube")
        {
            PxBoxGeometry geometry = PxBoxGeometry(Vector3(radius, radius, radius));
            PxShape* shape = body->createShape(geometry, *mat);
            item = new RenderItem(shape, body, color);
        }
        else 
        {
            PxSphereGeometry geometry = PxSphereGeometry(radius);
            PxShape* shape = body->createShape(geometry, *mat);
            item = new RenderItem(shape, body, color);
        }

        body->setMass(mass);
        gScene->addActor(*body);
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
    inline bool hasToDie() { return dead; }
    void clearForces() { body->clearForce(); }

    void Update(float t);
};
