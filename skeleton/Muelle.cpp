#include "Muelle.h"
using namespace physx;

Muelle::Muelle(Vector3 _pos, double _k, double resting_length, double Dumping, double Masa) : Centro(_pos), K(_k), L(resting_length)
{
	mParticle = new Particle(_pos, Vector3(0,0.1,0), Vector3(0, 0, 0), Dumping, Masa);
	Render();
}

Muelle::~Muelle()
{
}

void Muelle::integrate(double t)
{
	Vector3 f;

	Vector3 relativePos = Centro - mParticle->getPos();

	f = relativePos * (relativePos.normalize() - L) * K;

	mParticle->AddFuerza(f);
	
	for (int j = 0; j < myForces.size(); j++) {
		if (myForces[j]->Afecta(mParticle)) {
			myForces[j]->AddForce(mParticle, t);			
		}
	}	
	mParticle->integrate(t);
	Render();
}

void Muelle::Render()
{
	if (renderCentro != nullptr) renderCentro->release();	

	PxShape* _s = CreateShape(PxBoxGeometry(1,1,1));

	Vector4 v(0.5, 0.5, 0.5, 1);

	PxTransform* _t = new PxTransform(Centro);
	renderCentro = new RenderItem(_s, _t, v);
}
