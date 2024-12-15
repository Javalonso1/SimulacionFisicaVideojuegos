#pragma once
#include "RenderUtils.hpp"
using namespace physx;

class SolidRigidDynamic
{
public:
	SolidRigidDynamic(PxScene* sc, PxPhysics* p, PxTransform* t, PxShape* s, PxMaterial* m, double d);
	~SolidRigidDynamic();

	void addForce(Vector3 v);

	physx::PxTransform* _p() { return mTransform; }

	//physx::PxRigidDynamic* mRD() { return mRigidDynamic; }
private:
	PxScene* gScene;
	PxPhysics* gPhysics;
	PxRigidDynamic* mRigidDynamic;
	PxMaterial* mMaterial;
	PxTransform* mTransform;
	RenderItem* mRender;
	double _density;
};

