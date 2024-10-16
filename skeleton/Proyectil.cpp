#include "Proyectil.h"


Proyectil::Proyectil(Vector3 Pos, Vector3 Vel, double grv, double Dumping, double Masa) : gravedad(grv)
{
	mParticle = new Particle(Pos, Vel, Vector3(0,gravedad,0), Dumping, Masa);
}

Proyectil::~Proyectil()
{
	delete mParticle;
}

void Proyectil::Render()
{
	mParticle->Render();
}

void Proyectil::integrate(double t)
{
	mParticle->integrate(t);
}

