#include "SolidRigidDynamic.h"

SolidRigidDynamic::SolidRigidDynamic(PxScene* sc, PxPhysics* p, PxTransform* t, PxShape* s, PxMaterial* m, double d) : gScene(sc), gPhysics(p), mMaterial(m), _density(d)
{
	mRigidDynamic = gPhysics->createRigidDynamic(*t);
	mRigidDynamic->attachShape(*s);

	PxRigidBodyExt::updateMassAndInertia(*mRigidDynamic, _density);

	gScene->addActor(*mRigidDynamic);

	mRender = new RenderItem(s, mRigidDynamic, Vector4(1, 1, 1, 1));
}
