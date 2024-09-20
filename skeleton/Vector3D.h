#pragma once
class Vector3D
{
protected:
	float x;
	float y;
	float z;	

public:
	Vector3D() : x(0.0f), y(0.0f), z(0.0f){}
	Vector3D(float _x, float _y, float _z):x(_x), y(_y), z(_z) {}

	void Normalizar() {		
		if (x > y) {
			if (x > z) _normX(); //x es el mayor							
			else _normZ(); //z es el mayor			
		}
		else {
			if (y > z) _normY(); //y es el mayor							
			else _normZ(); //z es el mayor			
		}
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
};

