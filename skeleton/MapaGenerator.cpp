#include "MapaGenerator.h"

MapaGenerator::MapaGenerator(PxScene* gScene, PxPhysics* gPhysics, PxMaterial* mMat, SistemaParticulas* sp)
{	
	int esquinaX;
	int esquinaY;
	if (SIZE_MAP_X % 2 == 0) esquinaX = SIZE_MAP_X * -0.5f;
	else esquinaX = (SIZE_MAP_X -1) * -0.5f;
	if (SIZE_MAP_Y % 2 == 0) esquinaY = SIZE_MAP_Y * -0.5f;
	else esquinaY = (SIZE_MAP_Y - 1) * -0.5f;

	for (int i = 1; i <= SIZE_MAP_X; i++) {
		for (int j = 0; j < SIZE_MAP_Y; j++) {			
			SolidRigidStatic* sol;
			if(MAPA[SIZE_MAP_X-i][j] == 1)	sol = new SolidRigidStatic(gScene, gPhysics, new PxTransform((esquinaX + i)* TAM_CASILLA*2, 0, (esquinaY + j)* TAM_CASILLA*2), CreateShape(PxBoxGeometry(TAM_CASILLA, 0.1, TAM_CASILLA)), mMat, 0.01, 0.4, 0.01);
			else if (MAPA[SIZE_MAP_X - i][j] == 0)	sol = new SolidRigidStatic(gScene, gPhysics, new PxTransform((esquinaX + i)* TAM_CASILLA*2, 0, (esquinaY + j)* TAM_CASILLA*2), CreateShape(PxBoxGeometry(TAM_CASILLA, 0.1, TAM_CASILLA)), mMat, 0.01, 0.01, 1);

			mTiles.push_back(sol);
		}
	}

	for (int i = 0; i < NUM_FACTORIES; i++) {
		Factory* f = new Factory(gScene, gPhysics, new PxTransform(FACT_POS_X[i], TAM_CASILLA, FACT_POS_Y[i]), CreateShape(PxBoxGeometry(2, 3, 2)), mMat, sp);
		mFactories.push_back(f);
	}
}

MapaGenerator::~MapaGenerator()
{
	for (int i = mTiles.size() - 1; i >= 0; i--) {
		delete mTiles[i];
	}
	for (int i = mFactories.size() - 1; i >= 0; i--) {
		delete mFactories[i];
	}
}

void MapaGenerator::ApplyForce(ForceGenerator* f)
{
	for (int i = 0; i < mFactories.size(); i++) {
		mFactories[i]->ApplyForce(f);
	}
}

void MapaGenerator::RemoveForce(int j)
{
	for (int i = 0; i < NUM_FACTORIES; i++) {
		mFactories[i]->RemoveForce(j);
	}
}
