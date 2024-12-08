#pragma once
#include "RenderUtils.hpp"
struct PartGen {
public:
	PartGen(Vector3 vel, Vector3 acel, float dumping, double masa, double _genTime,
		double _elimTime, double _variation) :Vel(vel),Acel(acel),Dumping(dumping),
		Masa(masa),genTime(_genTime),elimTime(_elimTime), variation(_variation), porTiempo(true){
		
	}
	PartGen(Vector3 vel, Vector3 acel, float dumping, double masa, double _genTime,
		Vector3 _elimDist, double _variation) :Vel(vel), Acel(acel), Dumping(dumping),
		Masa(masa), genTime(_genTime), elimDist(_elimDist), variation(_variation), porTiempo(false) {

	}
	Vector3 Vel;
	Vector3 Acel;
	float Dumping;
	double Masa; 
	double genTime;
	bool porTiempo; //Si es por tiempo, true
	double elimTime;
	Vector3 elimDist;
	double variation;
};

const PartGen manguera(Vector3(0, 30, 0), Vector3(0, -9.8, 0), 0.98, 32, 0, Vector3(50, 80, 50), 6);
const PartGen PruebaFuerzas1(Vector3(0, 30, 0), Vector3(0, 0, 0), 0.98, 32, 0, 25, 6);
const PartGen PruebaFuerzas2(Vector3(0, -20, 0), Vector3(0, 0, 0), 0.98, 190, 0, 25, 6);
const PartGen PruebaFuerzas3(Vector3(0, 0, 0), Vector3(0, 0, 0), 0.98, 20, 0, 250, 3);