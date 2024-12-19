#pragma once
#include "RenderUtils.hpp"
#include "SolidRigidDynamic.h"
#include "ForceGenerator.h"
class Barco
{
public:
	Barco(PxScene* sc, PxPhysics* p, PxTransform* t);
	~Barco();

	void integrate(double t);
	void AddForce(ForceGenerator* f) { myForces.push_back(f); }

	void RemoveForce(int i) { myForces.erase(myForces.begin() + i); }
private:
	SolidRigidDynamic* mSol;
	std::vector<ForceGenerator*> myForces;
};

