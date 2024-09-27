#pragma once
#include "RenderUtils.hpp"
using namespace physx;

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	~Particle();

	void integrate(double t);
private:
	Vector3 vel;
	physx::PxTransform pos;
	RenderItem* renderItem;
};

