#pragma once
#include "RenderUtils.hpp"
using namespace physx;
class SolidRigidStatic
{
public:
	SolidRigidStatic(PxScene* sc,PxPhysics* p, PxTransform* t, PxShape* s, PxMaterial* m);
	SolidRigidStatic(PxScene* sc, PxPhysics* p, PxTransform* t, PxShape* s, PxMaterial* m, float r, float g, float b);
	~SolidRigidStatic();
private:
	PxScene* gScene;
	PxPhysics* gPhysics;
	PxRigidStatic* mRigidStatic;
	PxMaterial* mMaterial;
	RenderItem* mRender;
};

