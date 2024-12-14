#pragma once
#include "RenderUtils.hpp"
#include "Particle.h"
#include "ForceGenerator.h"
class Muelle
{
public:
	Muelle(Vector3 _pos, double _k, double resting_length, double Dumping, double Masa);
	~Muelle();

	void integrate(double t);	

	void Render();

	void AddForce(ForceGenerator* f) { myForces.push_back(f); }
private:
	Vector3 Centro;
	double K;
	double L;
	RenderItem* renderCentro = nullptr;
	Particle* mParticle;
	physx::PxTransform pos;

	std::vector<ForceGenerator*> myForces;
};

