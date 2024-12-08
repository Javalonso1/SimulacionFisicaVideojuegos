#pragma once
#include "Particle.h"
class ForceGenerator
{
public:
	enum TipeForces{ Viento, Torbellino, Gravedad};
	ForceGenerator(TipeForces t, Vector3 _v);
	ForceGenerator(TipeForces t, Vector3 _v, Vector3 _p1, Vector3 _p2);
	~ForceGenerator();

	void configCentroTorbellino(Vector3 _v) { _torbCenter = _v; }
	void configRadioTorbellino(double _r) { _torbRadius = _r; }
	void configPosYTorbellino(float _y) { _torbPosY = _y; }
	bool Afecta(Particle* p);

	void AddForce(Particle* p);
private:
	TipeForces myTipeforce;
	Vector3 v;
	Vector3 Point1;
	Vector3 Point2;
	
	bool Global;
	bool Area;

	//Para el torbellino
	Vector3 _torbCenter = Vector3(0, 0, 0);
	double _torbRadius = 100;
	float _torbPosY = 0;
};