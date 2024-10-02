#include "Particle.h"


Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel,  double Dumping) : vel(Vel), pos(PxTransform(Pos)), acel(Acel), dumping(Dumping)
{
	Render();
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{
	
	ModifyVel(t-_timePassed);
	pos.p = pos.p + (vel *(t - _timePassed))* dumping;
	Render();
	_timePassed = t;
}
void Particle::Render() {
	if(renderItem != nullptr) renderItem->release();
	
	PxShape* _s = CreateShape(PxSphereGeometry(1));

	Vector4 v(1, 1, 1, 1);

	PxTransform* _t = new PxTransform(pos.p);
	renderItem = new RenderItem(_s, _t, v);
}
void Particle::ModifyVel(double t) {
	vel = vel + acel*t* dumping;
}