#include "SolidRigidStatic.h"

SolidRigidStatic::SolidRigidStatic(PxScene* sc, PxPhysics* p, PxTransform* t, PxShape* s, PxMaterial* m): gScene(sc),gPhysics(p), mMaterial(m)
{
	mRigidStatic = gPhysics->createRigidStatic(*t);
	mRigidStatic->attachShape(*s);	

	//PxRigidBodyExt::updateMassAndInertia(*mRigidStatic, 0.15);

	gScene->addActor(*mRigidStatic);

	mRender = new RenderItem(s, mRigidStatic, Vector4(1, 1, 1, 1));
}
