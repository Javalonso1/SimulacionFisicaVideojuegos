#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include "Proyectil.h"
#include "SistemaParticulas.h"
#include "ForceGenerator.h"
#include "Muelle.h"
#include "SolidRigidStatic.h"
#include "SolidRigidDynamic.h"
#include "GeneradorSolidosRigidos.h"
//#include "Particle.h"
//#include "Vector3D.h"

#include <iostream>

std::string display_text = "";


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

std::vector<Proyectil*> _p;
SistemaParticulas* _Ps;
GeneradorParticulas* _g;
GeneradorSolidosRigidos* _gSR;
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
	
	_Ps = new SistemaParticulas();
	
	SolidRigidStatic* sol = new SolidRigidStatic(gScene, gPhysics, new PxTransform(0,0,0), CreateShape(PxBoxGeometry(100,0.1,100)), gMaterial);
	_gSR = new GeneradorSolidosRigidos(new PxTransform(0, 50, 0), Vector3(0,0,0), 2, 80, 10, gScene, gPhysics, CreateShape(PxBoxGeometry(1, 1, 1)), gMaterial, 0.15);
	//SolidRigidDynamic* din = new SolidRigidDynamic(gScene, gPhysics, new PxTransform(0, 50, 0), CreateShape(PxBoxGeometry(6, 6, 6)), gMaterial, 0.15);
	
	//Muelle* m = new Muelle(Vector3(0, 30, 0), 100, 10, 0.98, 32);
	//Muelle* m = new Muelle(Vector3(0, 30, 0), 400, 25, 0.98, 32, new Particle(Vector3(0, 30, 20), Vector3(0, 0.1, 0), Vector3(0, 0, 0), 0.98, 32));
	//m->AddForce(new ForceGenerator(ForceGenerator::Gravedad, Vector3(0, 0, 0)));
	//m->AddForce(new ForceGenerator(ForceGenerator::Viento, Vector3(0, 0, 150)));
	//_Ps->AddMuelle(m);

	//_Ps->AddGenerator(Vector3(0, 0, 0), Vector3(0, 30, 0), Vector3(0, -9.8, 0), 0.98, 32,		0, Vector3(50, 80, 50), 6);
	/*
	_g =_Ps->AddGenerator(Vector3(0, 31, 0), PruebaFuerzas4);
	_g->maxParticulas(1);
	_g->AddForce(new ForceGenerator(ForceGenerator::Gravedad, Vector3(0, 10, 0)));
	_g->AddForce(new ForceGenerator(ForceGenerator::Flotacion, Vector3(0, 30, 0)));

	PxShape* _s = CreateShape(PxBoxGeometry(100, 0.1, 100));

	Vector4 v(0, 0, 1, 0.5);

	PxTransform* _t = new PxTransform(Vector3(0,30,0));
	RenderItem* r = new RenderItem(_s, _t, v);
	*/

	//GeneradorParticulas* _g2 = _Ps->AddGenerator(Vector3(0, 0, 0), PruebaFuerzas2);
	/*
	ForceGenerator* _f = new ForceGenerator(ForceGenerator::Torbellino, Vector3(0, 0, 10));
	_f->configRadioTorbellino(15000);
	_g->AddForce(_f);
	*/
	//_g->AddForce(new ForceGenerator(ForceGenerator::Viento, Vector3(0, 0, 150)));
	//_g->AddForce(new ForceGenerator(ForceGenerator::Gravedad, Vector3(0, 0, 0)));
	//_g->AddForce(new ForceGenerator(ForceGenerator::Viento, Vector3(0, 0, 15), Vector3(-10,-10,-10), Vector3(10, 10, 10)));
	//_g2->AddForce(new ForceGenerator(ForceGenerator::Viento, Vector3(0, 0, 15)));
	//	_Ps->AddGenerator(Vector3(0, 0, 0), Vector3(0, 90, 0), Vector3(0, -9.8, 0), 0.98, 32,		0, 3, 6);

	/*
	Vector3D v(0,15,0);
	PxShape* _s = CreateShape(PxSphereGeometry(15));

	Vector4 v(0,1,1,1);

	PxTransform* _t = new PxTransform(Vector3(0,0,0));

	RenderItem* esferan = new RenderItem(_s,_t,v);*/
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	_Ps->integrate(t);

	_gSR->integrate(t);

	for(int i = 0; i < _p.size(); i++)
		_p[i]->integrate(t);

}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
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
	
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{	
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case ' ':
	{
		break;
	}
	case 'Q':
	{		
		Camera* c;
		c = GetCamera();		
		_p.push_back(new Proyectil(c->getTransform().p, c->getDir() * 50, -9.8, 0.98, 32));
		break;
	}
	case 'E':
	{		
		ForceGenerator* _f = new ForceGenerator(ForceGenerator::Explosion, Vector3(0, 0, 700));				
		if(_g!=nullptr)_g->AddForce(_f);
		if(_gSR!=nullptr)_gSR->AddForce(_f);
		break;
	}
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