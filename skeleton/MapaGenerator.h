#pragma once
#include "SolidRigidStatic.h"
#include "Constants.h"
#include "Factory.h"
#include "SistemaParticulas.h"
#include "ForceGenerator.h"
#include <vector>
class MapaGenerator
{
public:
	MapaGenerator(PxScene* gScene, PxPhysics* gPhysics, PxMaterial* mMat, SistemaParticulas* sp);
	~MapaGenerator();

	void ApplyForce(ForceGenerator*f);
	void RemoveForce(int i);
private:
	std::vector<SolidRigidStatic*> mTiles;
	std::vector<Factory*> mFactories;
};

