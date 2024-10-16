#include "SistemaParticulas.h"
#include <random>

SistemaParticulas::SistemaParticulas(Vector3 Pos, Vector3 Vel, Vector3 Acel, float Dumping, double Masa, double genTime,
										double elimTime, double variation) : vel(Vel), pos(Pos), acel(Acel),dumping(Dumping), 
										masaReal(Masa), GenTime(genTime), ElimTime(elimTime), Variation(variation), timeToNew(0)
{
	CreateParticle();
}

SistemaParticulas::~SistemaParticulas()
{
	for (int i = p.size() - 1; i >= 0; i--) {
		delete p[i];
	}
}

void SistemaParticulas::integrate(double t)
{
	timeToNew += t;
	if (timeToNew >= GenTime) {
		timeToNew -= GenTime;
		CreateParticle();
	}
	for (int i = 0; i < p.size(); i++) {
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
}

void SistemaParticulas::Render()
{
	//for (int i = 0; i < p.size(); i++) p[i].Render();
}

void SistemaParticulas::CreateParticle()
{		
	std::random_device rd{};
	std::mt19937 gen{ rd() };	
	std::normal_distribution<double> normal_x(vel.x, Variation);
	double _x = normal_x(gen);
	std::normal_distribution<double> normal_y(vel.y, Variation);
	double _y = normal_y(gen);
	std::normal_distribution<double> normal_z(vel.z, Variation);
	double _z = normal_z(gen);
	Vector3 _v(_x,_y,_z);	

	Particle* _p = new Particle(pos, _v, acel, dumping, masaReal);
	p.push_back(_p);
	time_p.push_back(0);
}
