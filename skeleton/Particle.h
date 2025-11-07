#pragma once
#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

using namespace physx;

class Particle {
public:
	enum Mode {
		EULER,
		SI_EULER,
		VERLET,
		POST_VERLET
	};

protected:
	RenderItem* item;
	PxTransform* pos;

	Vector3 force;
	Vector3 v;
	Vector3 a;

	double invM;
	double tVida;
	double damping;
	Vector3 lasPos;
	Vector4 colour;
	Mode mode;
	Vector3 originalPos;

	bool dead = false;

public:
	Particle() : pos(new PxTransform({ 0, 0, 0 })), v(0, 0, 0), a(0, 0, 0), invM(1.0), tVida(10), damping(1.0), lasPos(0, 0, 0), mode(EULER), colour({ 1, 0, 0, 1 }), originalPos(pos->p), force(0, 0, 0) {
		auto geom = PxSphereGeometry(1.0f);
		auto shape = CreateShape(geom);
		item = new RenderItem(shape, pos, colour);
	}

	Particle(Vector3 P, Vector3 V, Vector3 A, double T, double d, double M, Mode mod, Vector4 c = {0,0,0,0}) : pos(new PxTransform(P)), invM(pow(M, -1)), v(V), a(A), tVida(T), damping(d), lasPos(0, 0, 0), mode(mod), colour(c), originalPos(P), force(0, 0, 0) {
		auto geom = PxSphereGeometry(1.0f);
		auto shape = CreateShape(geom);
		item = new RenderItem(shape, pos, colour);
	}

	~Particle() { item->release(); pos = nullptr; }


	void Integrate(double t);
	inline void setMode(Mode m) { mode = m; }

	inline bool hasToDie() { return dead; }
	inline bool isFarFromOrigin(double distance) { if (((pos->p - originalPos).magnitude() > distance)) { dead = true; return dead; } return false; }
	inline void addForce(Vector3 const& nForce) { force += nForce; }
	inline void clearForce() { force = { 0, 0, 0 }; a = { 0, 0, 0 }; }
	inline void setStatic() { invM = 0; }

	inline Vector3 getPos() { return pos->p; }
	inline Vector3 getVelocity() { return v; }
	inline double getMass() { return pow(invM, -1); }
	inline Vector3 getForce() { return force; }
	double SetSimulatedVel(double simulatedVel);
};
