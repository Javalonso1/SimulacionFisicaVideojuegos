#include "SistemaParticulas.h"

SistemaParticulas::SistemaParticulas()
{
}

SistemaParticulas::~SistemaParticulas()
{
	for (int i = 0; i < gen.size(); i++) {
		delete gen[i];
	}
}

void SistemaParticulas::integrate(double t)
{
	for (int i = 0; i < gen.size(); i++) {
		gen[i]->integrate(t);
	}
	for (int i = 0; i < mue.size(); i++) {
		mue[i]->integrate(t);
	}
}

void SistemaParticulas::AddGenerator(Vector3 Pos, Vector3 Vel, Vector3 Acel, float Dumping, double Masa, double GenTime, double elimTime, double variation)
{
	gen.push_back(new GeneradorParticulas(Pos, Vel,Acel,Dumping,Masa,GenTime,elimTime,variation));
}

GeneradorParticulas* SistemaParticulas::AddGenerator(Vector3 Pos, Vector3 Vel, Vector3 Acel, float Dumping, double Masa, double GenTime, Vector3 elimDist, double variation)
{
	GeneradorParticulas* _g = new GeneradorParticulas(Pos, Vel, Acel, Dumping, Masa, GenTime, elimDist, variation);
	gen.push_back(_g);
	return _g;
}

GeneradorParticulas* SistemaParticulas::AddGenerator(Vector3 Pos, PartGen g)
{
	GeneradorParticulas* _g = new GeneradorParticulas(Pos, g);
	gen.push_back(_g);
	return _g;
}

void SistemaParticulas::RemoveGenerator(int i)
{
	delete gen[i];
	gen.erase(gen.begin() + i);
}

void SistemaParticulas::AddMuelle(Muelle* m)
{
	mue.push_back(m);
}
