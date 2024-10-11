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
private:
	Vector3 vel;
	Vector3 acel;	
	physx::PxTransform pos;
	RenderItem* renderItem = nullptr;	
	float dumping;
	double masaReal;
	void ModifyVel(double t);
};

