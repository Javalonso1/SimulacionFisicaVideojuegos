#pragma once
#include "RenderUtils.hpp"
using namespace physx;

class SolidRigidDynamic
{
public:
	SolidRigidDynamic(PxScene* sc, PxPhysics* p, PxTransform* t, PxShape* s, PxMaterial* m, double d);
private:
	PxScene* gScene;
	PxPhysics* gPhysics;
	PxRigidDynamic* mRigidDynamic;
	PxMaterial* mMaterial;
	RenderItem* mRender;
	double _density;
};

