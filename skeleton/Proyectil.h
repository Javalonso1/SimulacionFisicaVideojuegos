#pragma once
#include "RenderUtils.hpp"
#include "Particle.h"
class Proyectil
{
public:
	Proyectil(Vector3 Pos, Vector3 Vel, double grv, double Dumping);
	~Proyectil();

	void Render();
	void integrate(double t);
private:
	Particle* mParticle;
	double gravedad;
};

