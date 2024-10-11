#pragma once
#include "RenderUtils.hpp"
using namespace physx;

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Dumping);
	~Particle();

	void integrate(double t);

	
	void Render();
private:
	Vector3 vel;
	Vector3 acel;	
	physx::PxTransform pos;
	RenderItem* renderItem = nullptr;	
	float dumping;
	void ModifyVel(double t);
};

