#pragma once
#include "RenderUtils.hpp"
#include "ForceGenerator.h"
#include "SolidRigidDynamic.h"
class GeneradorSolidosRigidos
{
public:
	GeneradorSolidosRigidos(PxTransform* Pos, Vector3 InitForce, double GenTime, double elimTime, int max,
		PxScene* sc, PxPhysics* p, PxShape* s, PxMaterial* m, double d);
	GeneradorSolidosRigidos(PxTransform* Pos, Vector3 InitForce, double GenTime, Vector3 elimDist, int max,
		PxScene* sc, PxPhysics* p, PxShape* s, PxMaterial* m, double d);
	~GeneradorSolidosRigidos();

	void integrate(double t);

	void AddForce(ForceGenerator* f) { myForces.push_back(f); }
	void maxObjs(int i) { maxObj = i; };
private:
	//Por tiempo
	double ElimTime;
	//Por distancia
	Vector3 ElimDist;
	//Si es por tiempo o distancia
	bool PorTiempo;

	PxTransform* pos;
	Vector3 initForce;
	double genTime;	

	int maxObj = -1;

	std::vector<ForceGenerator*> myForces;
	std::vector<SolidRigidDynamic*> myObjs;

	std::vector<double> time_obj;
	double timeToNew;
	void CreateObject();

	//Settings Obj
	PxScene* mScene; 
	PxPhysics* mPhysics;
	PxShape* mShape;
	PxMaterial* mMaterial;
	double mDensity;
};

