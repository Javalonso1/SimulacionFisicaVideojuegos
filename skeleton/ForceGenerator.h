#pragma once
#include "Particle.h"
#include "SolidRigidDynamic.h"
class ForceGenerator
{
public:
	enum TipeForces{ Viento, Torbellino, Gravedad, Explosion, Flotacion};
	ForceGenerator(TipeForces t, Vector3 _v);
	ForceGenerator(TipeForces t, Vector3 _v, Vector3 _p1, Vector3 _p2);
	~ForceGenerator();
	bool Afecta(Particle* p);
	bool Afecta(SolidRigidDynamic* obj);
	void AddForce(Particle* p, double t);
	void AddForce(SolidRigidDynamic* obj, double t);

	//Torbellino
	void configCentro(Vector3 _v) { Center = _v; }
	void configRadioTorbellino(double _r) { Radius = _r; }
	void configPosYTorbellino(float _y) { _torbPosY = _y; }
	//Flotacion
	void configLiquidDensity(float x) { _liquid_density = x; }
	void configVolume(float x) { _volume = x; }	

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
	//Para la flotación
	float _liquid_density = 1000;
	float _volume = 1;	
};