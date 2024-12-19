#pragma once
#include "RenderUtils.hpp"
using namespace physx;

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Dumping, double Masa);
	~Particle();

	void integrate(double t);


	void Render();

	double masaSim();

	physx::PxTransform _p() { return pos; }

	Vector3 Fuerza() { return fuerza; }

	void recalculateFuerza();	

	void AddFuerza(Vector3 f);

	Vector3 getVel() { return vel;}

	Vector3 getPos() { return pos.p; }

	void changeGray() { col = 0.5f; }

	void DeletePorPos(float x);
private:
	Vector3 vel;
	Vector3 acel;	
	Vector3 fuerza;
	physx::PxTransform pos;
	RenderItem* renderItem = nullptr;		
	float dumping;
	double masaReal;
	void ModifyVel(double t);
	float col = 1;
};

