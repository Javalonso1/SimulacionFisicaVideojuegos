#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel) : vel(Vel), pos(PxTransform(Pos))
{
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::integrate(double t)
{

}
