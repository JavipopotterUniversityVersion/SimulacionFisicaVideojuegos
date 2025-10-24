#pragma once
#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

using namespace physx;

class Particle{
public:
	enum Mode {
		EULER,
		SI_EULER,
		VERLET,
		POST_VERLET
	};

private:
	Mode mode;
	RenderItem* item;
	PxTransform* position;
	Vector3 velocity;
	Vector3 acceleration;
	double mass;
	double lifeTime;
	double damping;
	Vector3 lastPosition;

public:
	Particle() : position(new PxTransform({0, 0, 0})), velocity(0, 0, 0), acceleration(0, 0, 0), mass(1.0), lifeTime(10), damping(1.0), lastPosition(0, 0, 0), mode(EULER){
		auto geometry = PxSphereGeometry(1.0f);
		auto shape = CreateShape(geometry);
		item = new RenderItem(shape, position, Vector4(1,1,1,1));
	}

	Particle(Vector3 P, Vector3 V, Vector3 A, double T, double d, Mode mass, Vector4 color = {1,1,1,1}) : position(new PxTransform(P)), velocity(V), acceleration(A), mass(1.0), lifeTime(T), damping(d), lastPosition(0, 0, 0), mode(mass) {
		auto geom = PxSphereGeometry(1.0f);
		auto shape = CreateShape(geom);
		item = new RenderItem(shape, position, color);
	}

	~Particle() { DeregisterRenderItem(item); item = nullptr; position = nullptr; }


	void Integrate(double t);
	inline void setMode(Mode mass) { mode = mass; }

	bool hasToDie() { return lifeTime <= 0.0; }
};

