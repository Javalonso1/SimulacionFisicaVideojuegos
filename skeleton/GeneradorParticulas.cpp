#include "GeneradorParticulas.h"
#include <random>

GeneradorParticulas::GeneradorParticulas(Vector3 Pos, Vector3 Vel, Vector3 Acel, float Dumping, double Masa, double genTime,
	double elimTime, double variation) : vel(Vel), pos(Pos), acel(Acel), dumping(Dumping),
	masaReal(Masa), GenTime(genTime), ElimTime(elimTime), Variation(variation), timeToNew(0), PorTiempo(true)
{
	constant = Variation == 0;	
	CreateParticle();
}
GeneradorParticulas::GeneradorParticulas(Vector3 Pos, Vector3 Vel, Vector3 Acel, float Dumping, double Masa, double genTime,
	Vector3 elimDist, double variation) : vel(Vel), pos(Pos), acel(Acel), dumping(Dumping),
	masaReal(Masa), GenTime(genTime), ElimDist(elimDist), Variation(variation), timeToNew(0), PorTiempo(false)
{
	if (ElimDist.x < 0) ElimDist.x = ElimDist.x * -1;
	if (ElimDist.y < 0) ElimDist.y = ElimDist.y * -1;
	if (ElimDist.z < 0) ElimDist.z = ElimDist.z * -1;
	constant = Variation == 0;
	CreateParticle();
}

GeneradorParticulas::GeneradorParticulas(Vector3 Pos, PartGen g) : pos(Pos), vel(g.Vel), acel(g.Acel), dumping(g.Dumping),
masaReal(g.Masa), GenTime(g.genTime), Variation(g.variation), timeToNew(0), ElimDist(g.elimDist), ElimTime(g.elimTime), PorTiempo(g.porTiempo)
{
	if (!g.porTiempo) {
		if (ElimDist.x < 0) ElimDist.x = ElimDist.x * -1;
		if (ElimDist.y < 0) ElimDist.y = ElimDist.y * -1;
		if (ElimDist.z < 0) ElimDist.z = ElimDist.z * -1;
	}
	constant = Variation == 0;
	CreateParticle();
}

GeneradorParticulas::~GeneradorParticulas()
{
	for (int i = p.size() - 1; i >= 0; i--) {
		delete p[i];
	}
}

void GeneradorParticulas::integrate(double t)
{
	timeToNew += t;
	if (timeToNew >= GenTime) {
		timeToNew -= GenTime;
		CreateParticle();
	}
	for (int i = 0; i < p.size(); i++) {
		if (PorTiempo) {
			time_p[i] += t;
			if (time_p[i] >= ElimTime) {
				delete p[i];
				p.erase(p.begin() + i);
				time_p.erase(time_p.begin() + i);
				i--;
			}
			else {
				p[i]->integrate(t);
			}
		}
		else {
			if (p[i]->_p().p.x > pos.x + ElimDist.x || p[i]->_p().p.x < pos.x - ElimDist.x ||
				p[i]->_p().p.y >pos.y + ElimDist.y || p[i]->_p().p.y < pos.y - ElimDist.y ||
				p[i]->_p().p.z >pos.z + ElimDist.z || p[i]->_p().p.z < pos.z - ElimDist.z)
				{
				delete p[i];
				p.erase(p.begin() + i);				
				i--;
			}
			else {
				p[i]->integrate(t);
			}
		}
	}
}

void GeneradorParticulas::CreateParticle()
{
	double _x;
	double _y;
	double _z;
	if (constant) {
		_x = vel.x;
		_y = vel.y;
		_z = vel.z;
	}
	else {
		std::random_device rd{};
		std::mt19937 gen{ rd() };
		std::normal_distribution<double> normal_x(vel.x, Variation);
		_x = normal_x(gen);
		std::normal_distribution<double> normal_y(vel.y, Variation);
		_y = normal_y(gen);
		std::normal_distribution<double> normal_z(vel.z, Variation);
		_z = normal_z(gen);
	}
	Vector3 _v(_x, _y, _z);

	Particle* _p = new Particle(pos, _v, acel, dumping, masaReal);
	p.push_back(_p);
	if(PorTiempo) time_p.push_back(0);
}
