#include "Muelle.h"
using namespace physx;

Muelle::Muelle(Vector3 _pos, double _k, double resting_length, double Dumping, double Masa) : Centro(_pos), K(_k), L(resting_length)
{
	mParticle = new Particle(_pos, Vector3(0,0.1,0), Vector3(0, 0, 0), Dumping, Masa);
	Render();
}

Muelle::Muelle(Vector3 _pos, double _k, double resting_length, double Dumping, double Masa, Particle* p2) : Centro(_pos), K(_k), L(resting_length), mParticle2(p2)
{
	mParticle = new Particle(_pos, Vector3(0, 0.1, 0), Vector3(0, 0, 0), Dumping, Masa);
	Render();
}

Muelle::~Muelle()
{
	delete mParticle;
	delete mParticle2;
}

void Muelle::integrate(double t)
{
	for (int j = 0; j < myForces.size(); j++) {
		if (myForces[j]->Afecta(mParticle)) {
			myForces[j]->AddForce(mParticle, t);			
		}
	}
	if (mParticle2 == nullptr) {
		Vector3 f;

		Vector3 relativePos = Centro - mParticle->getPos();

		f = relativePos * (relativePos.normalize() - L) * K;

		mParticle->AddFuerza(f);
	}
	else {
		Vector3 f;

		Vector3 relativePos = mParticle2->getPos() - mParticle->getPos();
		f = relativePos * (relativePos.normalize() - L) * K;
		mParticle->AddFuerza(f);		
		for (int j = 0; j < myForces.size(); j++) {
			if (myForces[j]->Afecta(mParticle2)) {
				myForces[j]->AddForce(mParticle2, t);
			}
		}
		
		relativePos = mParticle->getPos() - mParticle2->getPos();
		f = relativePos * (relativePos.normalize() - L) * K;
		mParticle2->AddFuerza(f);

		mParticle2->integrate(t);
	}	
	mParticle->integrate(t);
	
	Render();
}

void Muelle::Render()
{
	if (renderCentro != nullptr) renderCentro->release();	

	if (mParticle2 == nullptr) {
		PxShape* _s = CreateShape(PxBoxGeometry(1, 1, 1));

		Vector4 v(0.5, 0.5, 0.5, 1);

		PxTransform* _t = new PxTransform(Centro);
		renderCentro = new RenderItem(_s, _t, v);
	}	
}
