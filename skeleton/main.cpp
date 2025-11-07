#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Gun.h"
#include "ParticleSystem.h"
#include "UniformGeneration.h"
#include "GaussianGeneration.h"
#include "Explosion.h"
#include "GravityGenerator.h"
#include "Floor.h"
#include "Player.h"
#include "Volcano.h"
#include "ParabolicMover.h"
#include "WindGenerator.h"

#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

Gun* mGun = nullptr;
Player* player;
Volcano* volcano;
ParticleSystem* cynder;
WindGenerator* wind;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	//<---------------AQUI HAGO MOVIDAS--------------------->

	mGun = new Gun({ 0, 0, 0 }, { 20, 20, 20 }, { 0, -9.8, 0 }, 10.0, 1.0, Particle::EULER, 10.0);

	//FORCE GENERATORS
	player = new Player(new Particle(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.0, 0.0, 1.0, Particle::VERLET, Vector4(0,0,1,1)));
	std::cout << player;

	Floor* floor = new Floor(Vector3(0,-1.5,0));
	volcano = new Volcano(Vector3(0, 300, 900), player);

	std::vector<ParticleGen*> gens;
	gens.push_back(new UniformGeneration({0,0,0}, {0,0,0}, 2, 1, 0, 200));
	std::vector<ForceGenerator*> forces;
	forces.push_back(new GravityGenerator({ 0,0,0 }, 0.3));
	wind = new WindGenerator({ 0,0,0 }, { 1000,1000,1000 }, { 400,50,5 });
	forces.push_back(wind);
	cynder = new ParticleSystem({ 0,0,0 }, gens, forces);
	}


void stepPhysics(bool interactive, double t)
{
	mGun->Update(t);
	player->Update(t);

	volcano->Update(t);
	cynder->Update(t);

	Vector3 dir = player->getPos() - GetCamera()->getEye();
	GetCamera()->setPosition(player->getPos() + Vector3(0, 5, -80));
	GetCamera()->setDirection(dir.getNormalized());
	cynder->SetPosition(player->getPos() + Vector3(-80,-80,-80));

	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	delete mGun;
	mGun = nullptr;

	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	delete cynder;
	delete player;
	delete volcano;
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	Vector3 player_dir = Vector3(0, 0, 0);
	if (toupper(key) == 'I') player_dir += Vector3(0, 0, 1);
	if (toupper(key) == 'K') player_dir += Vector3(0, 0, -1);
	if (toupper(key) == 'J') player_dir += Vector3(1, 0, 0);
	if (toupper(key) == 'L') player_dir += Vector3(-1, 0, 0);

	player->Move(player_dir);

	PxVec3 dir = camera.q.rotate({0,0,-1});
	switch(toupper(key))
	{
	case 'B':
		mGun->SetPosition(camera.p + dir * 10);
		mGun->SetRotation(camera.q);
		mGun->Shoot();
		break;
	case 'F':
		wind->Toggle();
		break;
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}