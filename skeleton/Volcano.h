#pragma once
#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "ParabolicMover.h"
#include "GaussianGeneration.h"
#include "Explosion.h"
#include "GravityGenerator.h"

#include "ParticleSystem.h"
#include "Player.h"

using namespace physx;

class Volcano {
private:
	RenderItem* item;
	PxTransform* position;
	std::vector<ParabolicMover*> movers;
	std::vector<ParticleSystem*> p_systems;
	Player* player;

public:
	Volcano(Vector3 pos, Player* player) : position(new PxTransform(pos)), player(player) {
		auto geometry = PxBoxGeometry(150, 150, 150);
		auto shape = CreateShape(geometry);
		item = new RenderItem(shape, position, Vector4(1, 0, 0, 0));

		movers = std::vector<ParabolicMover*>();
		for (int i = 0; i < 1; i++) {

			//METEOR GENERATOR
			std::vector<ParticleGen*> particle_generators;
			GaussianGeneration* gauss = new GaussianGeneration(pos, { 1,1,1 }, 0.4, 100, 0);
			particle_generators.push_back(gauss);
			gauss->setGradients(Vector4(1, 0, 0, 1), Vector4(1, 1, 0, 1));

			std::vector<ForceGenerator*> forces;
			auto explosion = new Explosion(pos, 50, 0.1, 100000);
			explosion->Disable();
			forces.push_back(explosion);

			ParticleSystem* meteor_system = new ParticleSystem(pos, particle_generators, forces);
			p_systems.push_back(meteor_system);
			movers.push_back(new ParabolicMover(meteor_system, pos, player->getPos()));
		}
	}

	~Volcano() {
		DeregisterRenderItem(item); 
		item = nullptr; 
		position = nullptr; 
		for (int i = 0; i < p_systems.size(); i++) {
			delete p_systems[i];
			delete movers[i];
		}
	}

	inline void setPos(Vector3 new_pos) { position->p = new_pos; }
	inline Vector3 getPos() { return position->p; }

	void Update(double t) {
		const float angularSpeed = PxPi / 1.0f;

		float time = static_cast<float>(PxGetPhysics().getTolerancesScale().speed * t);

		PxVec3 axis(
			sinf(t * 0.5f),
			cosf(t * 0.3f),
			sinf(t * 0.7f)
		);
		axis.normalize();

		PxQuat deltaRot(angularSpeed * t, axis);

		position->q = deltaRot * position->q;
		position->q.normalize();

		for (int i = 0; i < movers.size(); i++) {
			if (movers[i]->IsFinished()) {
				movers[i]->Reset(player->getPos());
			}
			movers[i]->Update(t);
		}

		for (int i = 0; i < p_systems.size(); i++) {
			p_systems[i]->Update(t);
		}
	}
};

