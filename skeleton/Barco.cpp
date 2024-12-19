#include "Barco.h"
#include <iostream>

Barco::Barco(PxScene* sc, PxPhysics* p, PxTransform* t)
{

	float aux1 = rand() % 100;
	float aux2 = rand() % 100;
	float aux3 = rand() % 100;

	PxMaterial* m = p->createMaterial(aux1/100.0f, aux2 / 100.0f, aux3 / 100.0f);	


	PxShape* s = CreateShape(PxBoxGeometry(1,1,1));

	aux1 = (rand() % 4000) +100;	
	mSol = new SolidRigidDynamic(sc, p,t,s,m, aux1 / 100.0f, 0.4, 0.2, 0.1);	
}

Barco::~Barco()
{
}

void Barco::integrate(double t)
{
	for (int j = 0; j < myForces.size(); j++) {
		if (myForces[j]->Afecta(mSol)) {
			myForces[j]->AddForce(mSol, t);
		}
	}
}
