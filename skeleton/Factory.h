#pragma once
#include "RenderUtils.hpp"
#include "SolidRigidStatic.h"
#include "GeneradorParticulas.h"
#include "SistemaParticulas.h"
class Factory
{
public:
	Factory(PxScene* sc, PxPhysics* p, PxTransform* t, PxShape* s, PxMaterial* m, SistemaParticulas* sP);
	~Factory();
	void ApplyForce(ForceGenerator* f) { gP->AddForce(f); }
	void RemoveForce(int i) { gP->RemoveForce(i); }
private:
	SolidRigidStatic* mFact;
	GeneradorParticulas* gP;
};

