#pragma once
#include "Particle.h"
class ForceGenerator
{
public:
	enum TipeForces{ Viento, Gravedad};
	ForceGenerator(TipeForces t, Vector3 _v);
	ForceGenerator(TipeForces t, Vector3 _v, Vector3 _p1, Vector3 _p2);
	~ForceGenerator();

	bool Afecta(Particle* p);

	void AddForce(Particle* p);
private:
	TipeForces myTipeforce;
	Vector3 v;
	Vector3 Point1;
	Vector3 Point2;
	
	bool Global;
	bool Area;
};

