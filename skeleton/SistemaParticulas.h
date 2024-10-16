#pragma once
#include "RenderUtils.hpp"
#include "Particle.h"
#include <vector>
class SistemaParticulas
{
public:
	SistemaParticulas(Vector3 Pos, Vector3 Vel, Vector3 Acel, float Dumping, double Masa,
						double GenTime, double elimTime, double variation);

	~SistemaParticulas();

	void integrate(double t);


	void Render();
private:
	double GenTime;
	double ElimTime;
	double Variation;
	Vector3 vel;
	Vector3 acel;
	Vector3 pos;
	float dumping;
	double masaReal;

	std::vector<Particle*> p;
	std::vector<double> time_p;
	double timeToNew;
	void CreateParticle();
};


