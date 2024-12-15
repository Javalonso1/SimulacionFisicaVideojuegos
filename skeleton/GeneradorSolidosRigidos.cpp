#include "GeneradorSolidosRigidos.h"

GeneradorSolidosRigidos::GeneradorSolidosRigidos(PxTransform* Pos, Vector3 InitForce, double GenTime, double elimTime, int max,
	PxScene* sc, PxPhysics* p, PxShape* s, PxMaterial* m, double d) :
	pos(Pos), initForce(InitForce), genTime(GenTime), timeToNew(0), ElimTime(elimTime), maxObj(max), PorTiempo(true),
	mScene(sc), mPhysics(p), mShape(s), mMaterial(m), mDensity(d)
{
	CreateObject();
}

GeneradorSolidosRigidos::GeneradorSolidosRigidos(PxTransform* Pos, Vector3 InitForce, double GenTime, Vector3 elimDist, int max,
	PxScene* sc, PxPhysics* p, PxShape* s, PxMaterial* m, double d) :
	pos(Pos), initForce(InitForce), genTime(GenTime), timeToNew(0), ElimDist(elimDist), maxObj(max), PorTiempo(false),
	mScene(sc), mPhysics(p), mShape(s), mMaterial(m), mDensity(d)
{
	if (ElimDist.x < 0) ElimDist.x = ElimDist.x * -1;
	if (ElimDist.y < 0) ElimDist.y = ElimDist.y * -1;
	if (ElimDist.z < 0) ElimDist.z = ElimDist.z * -1;

	CreateObject();
}

GeneradorSolidosRigidos::~GeneradorSolidosRigidos()
{
	for (int i = myObjs.size() - 1; i >= 0; i--) {
		delete myObjs[i];
	}
}

void GeneradorSolidosRigidos::integrate(double t)
{
	if (myObjs.size() < maxObj) {
		timeToNew += t;
		if (timeToNew >= genTime) {
			timeToNew -= genTime;
			CreateObject();
		}
	}
	for (int i = 0; i < myObjs.size(); i++) {
		for (int j = 0; j < myForces.size(); j++) {
			if (myForces[j]->Afecta(myObjs[i])) {
				myForces[j]->AddForce(myObjs[i], t);
			}
		}
	}
}

void GeneradorSolidosRigidos::CreateObject()
{
	SolidRigidDynamic* _d = new SolidRigidDynamic(mScene, mPhysics,pos,mShape,mMaterial,mDensity);
	myObjs.push_back(_d);
	if (PorTiempo) time_obj.push_back(0);
	_d->addForce(initForce);
}
