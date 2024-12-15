#pragma once
#include "RenderUtils.hpp"
using namespace physx;
class SolidRigidStatic
{
public:
	SolidRigidStatic(PxScene* sc,PxPhysics* p, PxTransform* t, PxShape* s, PxMaterial* m);
private:
	PxScene* gScene;
	PxPhysics* gPhysics;
	PxRigidStatic* mRigidStatic;
	PxMaterial* mMaterial;
	RenderItem* mRender;
};

