#include "Factory.h"
#include "Constants.h"


Factory::Factory(PxScene* sc, PxPhysics* p, PxTransform* t, PxShape* s, PxMaterial* m, SistemaParticulas* sP)
{
	mFact = new SolidRigidStatic(sc, p, t, s, m,0,0,0);
	gP = sP->AddGenerator(t->p, Vector3(0, 3, 0), Vector3(0, 0, 0), 0.98, 55, 1, Vector3(SIZE_MAP_X, TAMANO_CIELO, SIZE_MAP_Y), 0.3);
	gP->ChangeGray();
	gP->maxParticulas(MAX_PART_FACT);
}

Factory::~Factory()
{
}
