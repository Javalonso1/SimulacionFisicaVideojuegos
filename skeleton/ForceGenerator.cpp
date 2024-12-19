#include "ForceGenerator.h"
#include <cmath>
#include <iostream>
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
	if (myTipeforce == ForceGenerator::Torbellino) {		
		return (p->_p().p - Center).magnitude() < Radius;
	}
	else {
		if (Global) return true;
		if (Area) {
			return (p->_p().p.x > Point1.x && p->_p().p.x < Point2.x) &&
				(p->_p().p.y > Point1.y && p->_p().p.y < Point2.y) &&
				(p->_p().p.z > Point1.z && p->_p().p.z < Point2.z);
		}
		else 	return false;
	}

}

bool ForceGenerator::Afecta(SolidRigidDynamic* obj)
{
	if (myTipeforce == ForceGenerator::Torbellino) {
		return (obj->_p()->getGlobalPose().p - Center).magnitude() < Radius;
	}
	else {
		if (Global) return true;
		if (Area) {
			return (obj->_p()->getGlobalPose().p.x > Point1.x && obj->_p()->getGlobalPose().p.x < Point2.x) &&
				(obj->_p()->getGlobalPose().p.y > Point1.y && obj->_p()->getGlobalPose().p.y < Point2.y) &&
				(obj->_p()->getGlobalPose().p.z > Point1.z && obj->_p()->getGlobalPose().p.z < Point2.z);
		}
		else 	return false;
	}
}

void ForceGenerator::AddForce(Particle* p, double t)
{
	double r;
	Vector3 f;
	switch (myTipeforce)
	{
	case ForceGenerator::Viento:
		f = v - p->getVel();
		p->AddFuerza(f);
		break;
	case ForceGenerator::Explosion:
		_explT += t;
		r = (p->_p().p - Center).magnitude();
		if (r < Radius) {			
			double d;
			d = v.magnitude() / pow(r, 2);
			double xd = pow(2.7182818, (-1 * (_explT / _explTMax)));			
			d = d * xd;			
			f = p->_p().p - Center;
			p->AddFuerza(f*d);
		}		
		break;
	case ForceGenerator::Torbellino:
		f = Vector3(-1*(p->_p().p.z- Center.z), _torbPosY-(p->_p().p.y- Center.y), p->_p().p.x- Center.x);
		p->AddFuerza(f*v.magnitude());		
		p->AddFuerza((Center -p->_p().p)*v.magnitude()*0.75);
		break;
	case ForceGenerator::Gravedad:
		f = Vector3(0,p->masaSim()*-9.8, 0);
		p->AddFuerza(f);				
		break;
	case ForceGenerator::Flotacion:		
		float _height;
		_height= 1.0f;
		float h;
		h= p->getPos().y;
		float h0;
		h0= v.y;
		float immersed;
		if (h - h0 > _height * 0.5) {
			immersed = 0.0;
		}
		else if (h0 - h > _height * 0.5) {
			immersed = 1.0;
		}
		else {
			immersed = (h0 - h) / _height + 0.5;
		}
		f.y = _liquid_density * _volume * immersed * 9.8;				

		p->AddFuerza(f);

		break;
	default:
		break;
	}
}

void ForceGenerator::AddForce(SolidRigidDynamic* obj, double t)
{
	double r;
	Vector3 f;
	switch (myTipeforce)
	{
	case ForceGenerator::Viento:
		//f = v - p->getVel();
		obj->addForce(v);
		break;
	case ForceGenerator::Explosion:
		_explT += t;
		r = (obj->_p()->getGlobalPose().p - Center).magnitude();
		if (r < Radius) {
			double d;
			d = v.magnitude() / pow(r, 2);
			double xd = pow(2.7182818, (-1 * (_explT / _explTMax)));
			d = d * xd;
			f = obj->_p()->getGlobalPose().p - Center;
			obj->addForce(f*d);			
		}
		break;
	case ForceGenerator::Torbellino:
		f = Vector3(-1 * (obj->_p()->getGlobalPose().p.z - Center.z), _torbPosY - (obj->_p()->getGlobalPose().p.y - Center.y), obj->_p()->getGlobalPose().p.x - Center.x);
		obj->addForce(f * v.magnitude());
		break;
	case ForceGenerator::Flotacion:
		float _height;
		_height = 1.0f;
		float h;
		h = obj->_p()->getGlobalPose().p.y;
		float h0;
		h0 = v.y;
		float immersed;
		if (h - h0 > _height * 0.5) {
			immersed = 0.0;
		}
		else if (h0 - h > _height * 0.5) {
			immersed = 1.0;
		}
		else {
			immersed = (h0 - h) / _height + 0.5;
		}
		f.y = _liquid_density * _volume * immersed * 9.8;
		
		obj->addForce(f);
		break;
	default:
		break;
	}
}

