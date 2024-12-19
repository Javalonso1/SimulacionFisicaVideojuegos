#pragma once
#include "RenderUtils.hpp"
#include "GeneradorParticulas.h"
#include "Muelle.h"
#include <vector>
class SistemaParticulas
{
public:
	SistemaParticulas();

	~SistemaParticulas();

	void integrate(double t);

	void AddGenerator(Vector3 Pos, Vector3 Vel, Vector3 Acel, float Dumping, double Masa,
		double GenTime, double elimTime, double variation);
	GeneradorParticulas* AddGenerator(Vector3 Pos, Vector3 Vel, Vector3 Acel, float Dumping, double Masa,
		double GenTime, Vector3 elimDist, double variation);
	GeneradorParticulas* AddGenerator(Vector3 Pos, PartGen g);
	void RemoveGenerator(int i);
	void AddMuelle(Muelle*m);
	
private:
	std::vector<GeneradorParticulas*> gen;	
	std::vector<Muelle*> mue;
};


