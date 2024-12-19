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
#include "MapaGenerator.h"
#include "Constants.h"
#include "Barco.h"
//#include "Particle.h"
//#include "Vector3D.h"

#include <iostream>

std::string display_text =		"Pulsa C Para Ver los Controles";

std::string info_text1 = "";
std::string info_text2 = "";
std::string info_text3 = "";

std::string controls_title =	"";

std::string controls_camera =	"";
std::string controls_camera2 =	"";

std::string controls_nubes =	"";
std::string controls_nubes2 =	"";

std::string controls_viento =	"";
std::string controls_viento2 =	"";
std::string controls_viento3 =	"";
std::string controls_viento4 =	"";

std::string control_tornado =	"";
std::string control_tornado2 =	"";
std::string control_tornado3 =	"";
std::string control_tornado4 =	"";

std::string control_basura =	"";
std::string control_basura2 =	"";
std::string control_basura3 =	"";

std::string control_exit =		"";

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
MapaGenerator* map;
std::vector<ForceGenerator*> allForces;
std::vector<Barco*> allBarcos;

enum Modo {Default,Nube,Viento,Tornado,Delete};
Modo mModo = Default;
int maxNubes = 250;
int PotenciaViento = 25;
enum Direccion {Norte, Noroeste, Oeste, Suroeste, Sur, Sureste, Este, Noreste};
Direccion DirVient = Norte;
Vector3 dir(1,0,0);
int PotenciaTornado = 5;
int RadioTornado = 35;

int numVientos = 1;
int numTornados = 1;
int posElim = 0;

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



	map = new MapaGenerator(gScene, gPhysics, gMaterial, _Ps);

	_g = _Ps->AddGenerator(Vector3(0, 20, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.98, 15, 0, Vector3(SIZE_MAP_X* TAM_CASILLA, TAMANO_CIELO, SIZE_MAP_Y * TAM_CASILLA), 1);
	_g->setIniYLock(true);
	_g->maxParticulas(maxNubes);
	_g->setRandomSpawn();	

	ForceGenerator* f = new ForceGenerator(ForceGenerator::Flotacion, Vector3(0,2, 0));
	
	for (int i = 0; i < NUM_BARCOS; i++) {
		Barco* b = new Barco(gScene, gPhysics, new PxTransform(BARCOS_POS_X[i], 10, BARCOS_POS_Y[i]));
		b->AddForce(f);
		allBarcos.push_back(b);
	}
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

	if(_gSR!=nullptr)_gSR->integrate(t);

	for(int i = 0; i < _p.size(); i++)
		_p[i]->integrate(t);

	for (int i = 0; i < allBarcos.size(); i++)
		allBarcos[i]->integrate(t);
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
	case 'M':
	{
		controls_title = "";

		controls_camera = "";
		controls_camera2 = "";

		controls_nubes = "";
		controls_nubes2 = "";

		controls_viento = "";
		controls_viento2 = "";
		controls_viento3 = "";
		controls_viento4 = "";

		control_tornado = "";
		control_tornado2 = "";
		control_tornado3 = "";
		control_tornado4 = "";

		control_basura = "";
		control_basura2 = "";
		control_basura3 = "";

		control_exit = "";
		break;
	}
	case 'C':
	{		
		display_text = "";
		mModo = Default;
		info_text1 = "";
		info_text2 = "";
		info_text3 = "";

		controls_title = "CONTROLES";

		controls_camera = "W A S D  para mover la camara";
		controls_camera2 = "Q/E  para alejar/acercar la camara";

		controls_nubes = "N  para manejar las nubes";
		controls_nubes2 = "+/-  para aumentar/reducir las nubes";

		controls_viento =	"V  para manejar el viento";
		controls_viento2 = "+/-  para aumentar/reducir la potencia";
		controls_viento3 = "o/p  para cambiar la direccion";
		controls_viento4 =	"K  para generar viento";

		control_tornado = "T  para manejar los tornados";
		control_tornado2 = "+/-  para aumentar/reducir la potencia";
		control_tornado3 = "o/p  para aumentar/reducir el radio";
		control_tornado4 =	"K  para generar tornado";

		control_basura = "X  para destruir fuerzas";
		control_basura2 = "o/p  para seleccionar entre las fuerzas";
		control_basura3 =	"K  para destruir fuerza";

		control_exit = "M  para salir de los controles";
		break;
	}
	case 'V':
	{
		mModo = Viento;
		info_text1 = "Colocando: Viento";
		info_text2 = "Fuerza del Viento: ";
		info_text2 += std::to_string(PotenciaViento);
		info_text3 = "Direccion del Viento: ";
		std::string aux = "";
		switch (DirVient)
		{
		case Norte:
			aux = "Norte";
			break;
		case Noroeste:
			aux = "Noroeste";
			break;
		case Oeste:
			aux = "Oeste";
			break;
		case Suroeste:
			aux = "Suroeste";
			break;
		case Sur:
			aux = "Sur";
			break;
		case Sureste:
			aux = "Sureste";
			break;
		case Este:
			aux = "Este";
			break;
		case Noreste:
			aux = "Noroeste";
			break;
		default:
			break;
		}
		info_text3 += aux;

		controls_title = "";

		controls_camera = "";
		controls_camera2 = "";

		controls_nubes = "";
		controls_nubes2 = "";

		controls_viento = "";
		controls_viento2 = "";
		controls_viento3 = "";
		controls_viento4 = "";

		control_tornado = "";
		control_tornado2 = "";
		control_tornado3 = "";
		control_tornado4 = "";

		control_basura = "";
		control_basura2 = "";
		control_basura3 = "";

		control_exit = "";
		break;
	}
	case 'N':
	{
		mModo = Nube;
		info_text1 = "Controlando: Nubes";
		info_text2 = "Numero Particulas: ";
		info_text2 += std::to_string(maxNubes);
		info_text3 = "";

		controls_title = "";

		controls_camera = "";
		controls_camera2 = "";

		controls_nubes = "";
		controls_nubes2 = "";

		controls_viento = "";
		controls_viento2 = "";
		controls_viento3 = "";
		controls_viento4 = "";

		control_tornado = "";
		control_tornado2 = "";
		control_tornado3 = "";
		control_tornado4 = "";

		control_basura = "";
		control_basura2 = "";
		control_basura3 = "";

		control_exit = "";
		break;
	}
	case 'T':
	{
		mModo = Tornado;
		info_text1 = "Colocando: Tornados";
		info_text2 = "Fuerza del Tornado: ";
		info_text2 += std::to_string(PotenciaTornado);
		info_text3 = "Radio del Tornado: ";
		info_text3 += std::to_string(RadioTornado);

		controls_title = "";

		controls_camera = "";
		controls_camera2 = "";

		controls_nubes = "";
		controls_nubes2 = "";

		controls_viento = "";
		controls_viento2 = "";
		controls_viento3 = "";
		controls_viento4 = "";

		control_tornado = "";
		control_tornado2 = "";
		control_tornado3 = "";
		control_tornado4 = "";

		control_basura = "";
		control_basura2 = "";
		control_basura3 = "";

		control_exit = "";
		break;
	}
	case 'X':
	{
		mModo = Delete;
		info_text1 = "Eliminando: Fuerzas";
		if (allForces.size() == 0) {
			info_text2 = "No hay fuerzas para borrar";
			info_text3 = "";
		}
		else
		{
			posElim = 0;
			info_text2 = allForces[posElim]->getName();
			info_text3 = "Pulsa K para borrar";
		}

		controls_title = "";

		controls_camera = "";
		controls_camera2 = "";

		controls_nubes = "";
		controls_nubes2 = "";

		controls_viento = "";
		controls_viento2 = "";
		controls_viento3 = "";
		controls_viento4 = "";

		control_tornado = "";
		control_tornado2 = "";
		control_tornado3 = "";
		control_tornado4 = "";

		control_basura = "";
		control_basura2 = "";
		control_basura3 = "";

		control_exit = "";
		break;
	}
	case '+':
	{		
		switch (mModo)
		{
		case Nube:
			maxNubes += 25;
			info_text2 = "Numero Particulas: ";
			info_text2 += std::to_string(maxNubes);
			_g->maxParticulas(maxNubes);
			break;
		case Viento:
			PotenciaViento += 5;
			info_text2 = "Fuerza del Viento: ";
			info_text2 += std::to_string(PotenciaViento);
			break;
		case Tornado:
			PotenciaTornado ++;
			info_text2 = "Fuerza del Tornado: ";
			info_text2 += std::to_string(PotenciaTornado);
			break;
		case Delete:
			posElim++;
			if (posElim >= allForces.size()) posElim = 0;
			info_text2 = allForces[posElim]->getName();
			info_text3 = "Pulsa K para borrar";
			break;
		default:
			break;
		}
		break;
	}
	case '-':
	{
		switch (mModo)
		{
		case Nube:
			if(maxNubes >0) maxNubes -= 25;
			info_text2 = "Numero Particulas: ";
			info_text2 += std::to_string(maxNubes);
			_g->maxParticulas(maxNubes);
			break;
		case Viento:
			if(PotenciaViento >0)PotenciaViento -= 5;
			info_text2 = "Fuerza del Viento: ";
			info_text2 += std::to_string(PotenciaViento);
			break;
		case Tornado:
			if(PotenciaTornado >0)PotenciaTornado --;
			info_text2 = "Fuerza del Tornado: ";
			info_text2 += std::to_string(PotenciaTornado);
			break;
		case Delete:
			posElim--;
			if (posElim < 0) posElim = allForces.size()-1;
			info_text2 = allForces[posElim]->getName();
			info_text3 = "Pulsa K para borrar";
			break;
		default:
			break;
		}
		break;
	}
	case 'O':
	{
		std::string aux = "";
		switch (mModo)
		{
		case Viento:			

			info_text3 = "Dirección del Viento: ";
			switch (DirVient)
			{
			case Norte:
				DirVient = Noroeste;
				aux = "Noroeste";
				dir = Vector3(0.5,0,-0.5);
				break;
			case Noroeste:
				DirVient = Oeste;
				dir = Vector3(0, 0, -1);
				aux = "Oeste";
				break;
			case Oeste:
				DirVient = Suroeste;
				dir = Vector3(-0.5, 0, -0.5);
				aux = "Suroeste";
				break;
			case Suroeste:
				DirVient = Sur;
				dir = Vector3(-1, 0, 0);
				aux = "Sur";
				break;
			case Sur:
				DirVient = Sureste;
				dir = Vector3(-0.5, 0, 0.5);
				aux = "Sureste";
				break;
			case Sureste:
				DirVient = Este;
				dir = Vector3(0, 0, 1);
				aux = "Este";
				break;
			case Este:
				DirVient = Noreste;
				dir = Vector3(0.5, 0, 0.5);
				aux = "Noreste";
				break;
			case Noreste:
				DirVient = Norte;
				dir = Vector3(1, 0, 0);
				aux = "Norte";
				break;
			default:
				break;
			}
			info_text3 += aux;			
			break;
		case Tornado:
			if (RadioTornado > 0)RadioTornado -= 5;
			info_text3 = "Radio del Tornado: ";
			info_text3 += std::to_string(RadioTornado);
			break;
		case Delete:			
			break;
		default:
			break;
		}
		break;
	}
	case 'P':
	{
		std::string aux = "";
		switch (mModo)
		{
		case Viento:
			info_text3 = "Dirección del Viento: ";
			switch (DirVient)
			{
			case Norte:
				DirVient = Noreste;
				aux = "Noreste";
				dir = Vector3(0.5, 0, 0.5);
				break;
			case Noroeste:
				DirVient = Norte;
				dir = Vector3(1, 0, 0);
				aux = "Norte";
				break;
			case Oeste:
				DirVient = Noroeste;
				dir = Vector3(0.5, 0, -0.5);
				aux = "Noroeste";
				break;
			case Suroeste:
				DirVient = Oeste;
				dir = Vector3(0, 0, -1);
				aux = "Oeste";
				break;
			case Sur:
				DirVient = Suroeste;
				dir = Vector3(-0.5, 0, -0.5);
				aux = "Suroeste";
				break;
			case Sureste:
				DirVient = Sur;
				dir = Vector3(-1, 0, 0);
				aux = "Sur";
				break;
			case Este:
				DirVient = Sureste;
				dir = Vector3(-0.5, 0, 0.5);
				aux = "Sureste";
				break;
			case Noreste:
				DirVient = Este;
				dir = Vector3(0, 0, 1);
				aux = "Este";
				break;
			default:
				break;
			}
			info_text3 += aux;
			break;
		case Tornado:			
			RadioTornado += 5;
			info_text3 = "Radio del Tornado: ";
			info_text3 += std::to_string(RadioTornado);
			break;
		case Delete:
			break;
		default:
			break;
		}
		break;
	}
	case 'K': {
		std::string nom;
		switch (mModo)
		{		
		case Viento:
			allForces.push_back(new ForceGenerator(ForceGenerator::TipeForces::Viento, dir*PotenciaViento));
			nom = "Viento";
			nom += std::to_string(numVientos);
			allForces.back()->Name(nom);
			numVientos++;
			_g->AddForce(allForces.back());
			map->ApplyForce(allForces.back());
			for (int i = 0; i < allBarcos.size(); i++)
				allBarcos[i]->AddForce(allForces.back());
			break;
		case Tornado:			
			allForces.push_back(new ForceGenerator(ForceGenerator::TipeForces::Torbellino, Vector3(PotenciaTornado,0,0)));
			allForces.back()->configCentro(Vector3(GetCamera()->getTransform().p.x, 0, GetCamera()->getTransform().p.z));
			allForces.back()->configRadioTorbellino(RadioTornado);
			allForces.back()->configPosYTorbellino(40);
			nom = "Tornado";
			nom += std::to_string(numTornados);
			allForces.back()->Name(nom);
			numTornados++;
			_g->AddForce(allForces.back());
			map->ApplyForce(allForces.back());
			for (int i = 0; i < allBarcos.size(); i++)
				allBarcos[i]->AddForce(allForces.back());
			break;
		case Delete:
			if (allForces.size() > posElim) {
				_g->RemoveForce(posElim);				
				map->RemoveForce(posElim);
				for (int i = 0; i < allBarcos.size(); i++)
					allBarcos[i]->RemoveForce(posElim+1);
				allForces.erase(allForces.begin() + posElim);
			}
			break;
		default:
			break;
		}

		mModo = Default;
		info_text1 = "";
		info_text2 = "";
		info_text3 = "";
		break;
	}
	default:		
		/*
		Camera* c;
		c = GetCamera();		
		_p.push_back(new Proyectil(c->getTransform().p, c->getDir() * 50, -9.8, 0.98, 32));
		break;*/
		/*
		ForceGenerator* _f = new ForceGenerator(ForceGenerator::Explosion, Vector3(0, 0, 700));				
		if(_g!=nullptr)_g->AddForce(_f);
		if(_gSR!=nullptr)_gSR->AddForce(_f);
		break;*/
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