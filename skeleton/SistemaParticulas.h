#pragma once
#include "RenderUtils.hpp"
#include "GeneradorParticulas.h"
#include <vector>
class SistemaParticulas
{
public:
	SistemaParticulas();

	~SistemaParticulas();

	void integrate(double t);

	void AddGenerator(Vector3 Pos, Vector3 Vel, Vector3 Acel, float Dumping, double Masa,
		double GenTime, double elimTime, double variation);
	void AddGenerator(Vector3 Pos, Vector3 Vel, Vector3 Acel, float Dumping, double Masa,
		double GenTime, Vector3 elimDist, double variation);
	GeneradorParticulas* AddGenerator(Vector3 Pos, PartGen g);
	void RemoveGenerator(int i);
	
private:
	std::vector<GeneradorParticulas*> gen;	
};


