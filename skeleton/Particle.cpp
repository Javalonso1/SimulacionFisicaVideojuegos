#include "Particle.h"
#include <math.h>

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel,  double Dumping, double masa) : vel(Vel), pos(PxTransform(Pos)), acel(Acel), dumping(Dumping), masaReal(masa)
{
	Render();
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{	
	ModifyVel(t);
	pos.p = pos.p + (vel *t)* pow(dumping, t);
	Render();
}
void Particle::Render() {
	if(renderItem != nullptr) renderItem->release();
	
	PxShape* _s = CreateShape(PxSphereGeometry(1));

	Vector4 v(1, 1, 1, 1);

	PxTransform* _t = new PxTransform(pos.p);
	renderItem = new RenderItem(_s, _t, v);
}
double Particle::masaSim()
{	
	double aux = vel.magnitude()/vel.magnitude();
	return masaReal * pow(aux, 2);
}
void Particle::ModifyVel(double t) {
	vel = vel + acel * t;
}