#include "ForceGenerator.h"

ForceGenerator::ForceGenerator(TipeForces t, Vector3 _v) : myTipeforce(t), v(_v)
{	
	Global = true;
	Area = false;
}

ForceGenerator::ForceGenerator(TipeForces t, Vector3 _v, Vector3 _p1, Vector3 _p2) : myTipeforce(t), v(_v), Point1(_p1), Point2(_p2)
{
	Global = false;
	Area = true;

	float aux;
	if (Point1.x > Point2.x) {
		aux = Point1.x;
		Point1.x = Point2.x;
		Point2.x = aux;
	}
	if (Point1.y > Point2.y) {
		aux = Point1.y;
		Point1.y = Point2.y;
		Point2.y = aux;
	}
	if (Point1.z > Point2.z) {
		aux = Point1.z;
		Point1.z = Point2.z;
		Point2.z = aux;
	}
}

ForceGenerator::~ForceGenerator()
{
}

bool ForceGenerator::Afecta(Particle* p)
{
	if (Global) return true;
	if (Area) {
		return (p->_p().p.x > Point1.x && p->_p().p.x < Point2.x) &&
			(p->_p().p.y > Point1.y && p->_p().p.y < Point2.y) &&
			(p->_p().p.z > Point1.z && p->_p().p.z < Point2.z);		
	}

	return false;
}

void ForceGenerator::AddForce(Particle* p)
{
	Vector3 f;
	switch (myTipeforce)
	{
	case ForceGenerator::Viento:
		f = v - p->getVel();
		p->AddFuerza(f);
		break;
	case ForceGenerator::Gravedad:
		f = Vector3(0,p->masaSim()*-9.8, 0);
		p->AddFuerza(f);
		break;
	default:
		break;
	}
}

