#pragma once
#include <math.h>
#include "RenderUtils.hpp"
using namespace physx;
class Vector3D
{
protected:
	float x;
	float y;
	float z;	

public:
	Vector3D() : x(0.0f), y(0.0f), z(0.0f) { Render(); }
	Vector3D(float _x, float _y, float _z):x(_x), y(_y), z(_z) {Render();}

	void Normalizar() {		
		int _x = 1;
		if (x < 0) {
			_x = -1;
			x = x * -1;
		}
		int _y = 1;
		if (y < 0) {
			_y = -1;
			y = y * -1;
		}
		int _z = 1;
		if (z < 0) {
			_z = -1;
			z = z * -1;
		}

		if (x > y) {
			if (x > z) _normX(); //x es el mayor							
			else _normZ(); //z es el mayor			
		}
		else {
			if (y > z) _normY(); //y es el mayor							
			else _normZ(); //z es el mayor			
		}
		x = x * _x;
		y = y * _y;
		z = z * _z;
	}
	float Modulo() {
		float sol = x * x + y * y + z * z;		
		return sqrt(sol);
	}
	bool operator==(const Vector3D& v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}
	bool operator!=(const Vector3D& v) const
	{
		return !(x == v.x && y == v.y && z == v.z);
	}
	Vector3D operator+(const Vector3D& v) const {
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}
	Vector3D operator-(const Vector3D& v) const {
		return Vector3D(x -v.x, y - v.y, z - v.z);
	}
	float operator*(const Vector3D& v) const {
		//Cálculo producto escalar
		float sol = x * v.x + y * v.y + z * v.z;
		return sol;
	}
	Vector3D operator*(const float& v) const {
		return Vector3D(x*v, y*v, z*v);
	}
private:
	void _normX() {
		y = y / x;
		z = z / x;
		x = 1.0f;
	}
	void _normY() {
		x = x / y;
		z = z / y;
		y = 1.0f;
	}
	void _normZ() {
		x = x / z;
		y = y / z;
		z = 1.0f;
	}
	void Render() {
		PxShape* _s = CreateShape(PxSphereGeometry(1));

		Vector4 v(1, 1, 1, 1);

		PxTransform* _t = new PxTransform(Vector3(x, y, z));
		RenderItem* esferan = new RenderItem(_s, _t, v);

		v.y = 0;
		v.z = 0;		
		_t = new PxTransform(Vector3(x+10, y, z));
		esferan = new RenderItem(_s, _t, v);	

		v.y = 1;
		v.x = 0;		
		_t = new PxTransform(Vector3(x, y+10, z));
		esferan = new RenderItem(_s, _t, v);

		v.y = 0;
		v.z = 1;		
		_t = new PxTransform(Vector3(x, y, z+10));
		esferan = new RenderItem(_s, _t, v);
	}
};

