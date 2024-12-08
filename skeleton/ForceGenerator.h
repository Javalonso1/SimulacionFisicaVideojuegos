#pragma once
#include "Particle.h"
class ForceGenerator
{
public:
	enum TipeForces{ Viento, Torbellino, Gravedad, Explosion};
	ForceGenerator(TipeForces t, Vector3 _v);
	ForceGenerator(TipeForces t, Vector3 _v, Vector3 _p1, Vector3 _p2);
	~ForceGenerator();

	void configCentro(Vector3 _v) { Center = _v; }
	void configRadioTorbellino(double _r) { Radius = _r; }
	void configPosYTorbellino(float _y) { _torbPosY = _y; }
	bool Afecta(Particle* p);

	void AddForce(Particle* p, double t);
private:
	TipeForces myTipeforce;
	Vector3 v;
	Vector3 Point1;
	Vector3 Point2;
	
	bool Global;
	bool Area;

	Vector3 Center = Vector3(0, 0, 0);
	double Radius = 100;
	//Para el torbellino
	float _torbPosY = 0;
	//Para la explosion
	float _explT = 0;
	float _explTMax = 10;
};