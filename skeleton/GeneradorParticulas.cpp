#include "GeneradorParticulas.h"
#include <random>

GeneradorParticulas::GeneradorParticulas(Vector3 Pos, Vector3 Vel, Vector3 Acel, float Dumping, double Masa, double genTime,
	double elimTime, double variation) : vel(Vel), pos(Pos), acel(Acel), dumping(Dumping),
	masaReal(Masa), GenTime(genTime), ElimTime(elimTime), Variation(variation), timeToNew(0), PorTiempo(true)
{
	CreateParticle();
}
GeneradorParticulas::GeneradorParticulas(Vector3 Pos, Vector3 Vel, Vector3 Acel, float Dumping, double Masa, double genTime,
	Vector3 elimDist, double variation) : vel(Vel), pos(Pos), acel(Acel), dumping(Dumping),
	masaReal(Masa), GenTime(genTime), ElimDist(elimDist), Variation(variation), timeToNew(0), PorTiempo(false)
{
	if (ElimDist.x < 0) ElimDist.x = ElimDist.x * -1;
	if (ElimDist.y < 0) ElimDist.y = ElimDist.y * -1;
	if (ElimDist.z < 0) ElimDist.z = ElimDist.z * -1;
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
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::normal_distribution<double> normal_x(vel.x, Variation);
	double _x = normal_x(gen);
	std::normal_distribution<double> normal_y(vel.y, Variation);
	double _y = normal_y(gen);
	std::normal_distribution<double> normal_z(vel.z, Variation);
	double _z = normal_z(gen);
	Vector3 _v(_x, _y, _z);

	Particle* _p = new Particle(pos, _v, acel, dumping, masaReal);
	p.push_back(_p);
	if(PorTiempo) time_p.push_back(0);
}
