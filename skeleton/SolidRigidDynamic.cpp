#include "SolidRigidDynamic.h"

SolidRigidDynamic::SolidRigidDynamic(PxScene* sc, PxPhysics* p, PxTransform* t, PxShape* s, PxMaterial* m, double d) : gScene(sc), gPhysics(p), mMaterial(m), _density(d), mTransform(t)
{
	mRigidDynamic = gPhysics->createRigidDynamic(*t);
	mRigidDynamic->attachShape(*s);

	PxRigidBodyExt::updateMassAndInertia(*mRigidDynamic, _density);

	gScene->addActor(*mRigidDynamic);

	mRender = new RenderItem(s, mRigidDynamic, Vector4(1, 1, 1, 1));
}

SolidRigidDynamic::~SolidRigidDynamic()
{
}

void SolidRigidDynamic::addForce(Vector3 v)
{
	mRigidDynamic->addForce(v);
}