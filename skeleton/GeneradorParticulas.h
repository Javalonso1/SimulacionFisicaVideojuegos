#pragma once
#include "RenderUtils.hpp"
#include "Particle.h"
#include "Generators.h"
#include "ForceGenerator.h"
#include <vector>
class GeneradorParticulas
{
public:
	GeneradorParticulas(Vector3 Pos, Vector3 Vel, Vector3 Acel, float Dumping, double Masa,
		double GenTime, double elimTime, double variation);
	GeneradorParticulas(Vector3 Pos, Vector3 Vel, Vector3 Acel, float Dumping, double Masa,
		double GenTime, Vector3 elimDist, double variation);
	GeneradorParticulas(Vector3 Pos, PartGen g);

	~GeneradorParticulas();

	void integrate(double t);

	void AddForce(ForceGenerator* f) { myForces.push_back(f); }

	void RemoveForce(int i) { myForces.erase(myForces.begin() + i); }

	void maxParticulas(int i);

	void setRandomSpawn() {
		if (!PorTiempo) {
			randomSpawn = true;
		}
	}
	void setIniYLock(bool a) {
		IniYlock = a;
	}

	void ChangeGray() { colgris = true; }
private:
	//Por tiempo
	double ElimTime;
	//Por distancia
	Vector3 ElimDist;
	//Si es por tiempo o distancia
	bool PorTiempo;
	//Si usa desviación normal o es constante
	bool constant;

	bool randomSpawn;
	
	double Variation;
	double GenTime;
	Vector3 vel;
	Vector3 acel;
	Vector3 pos;
	float dumping;
	double masaReal;

	int maxPart = -1;

	bool IniYlock = false;	

	std::vector<ForceGenerator*> myForces;
	std::vector<Particle*> p;
	std::vector<double> time_p;
	double timeToNew;
	void CreateParticle();

	bool colgris = false;
};

