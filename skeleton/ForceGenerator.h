#pragma once
#include <list>
#include <PxPhysicsAPI.h>
#include "core.hpp"
class Particle;

class ForceGenerator
{
protected:
	Vector3 pos;
	bool enabled = true;
public:
	ForceGenerator(Vector3 pos) : pos(pos) {}
	~ForceGenerator() {}

	virtual void ApplyForce(const std::list<Particle*>& particles, double t) = 0;
	inline Vector3 getPos() { return pos; };
	inline void setPos(Vector3 new_pos) { pos = new_pos; }

	virtual void Enable() { enabled = true; }
	virtual void Disable() { enabled = false; }
	void Toggle() { enabled = !enabled;}
};
	 

