#include "metropolis_nvt.h"
#include <random>

MetropolisNVTUpdate::MetropolisNVTUpdate(ClassicalParticleSystem& system, double T, double k_b) :
  MetropolisUpdate(system) 
{
  setT(T, k_b);
}

void MetropolisNVTUpdate::setT(double new_t, double k_b)
{
  T = new_t;
  this->k_b = k_b;
  beta = 1. / (new_t * k_b);
}

double MetropolisNVTUpdate::getT() const
{
  return T;
}

void MetropolisNVTUpdate::RunUpdate() 
{
  const double previous_energy =
    static_cast<ClassicalParticleSystem&>(system).getKineticEnergy();
  RandomStep();
  const double new_energy =
    static_cast<ClassicalParticleSystem&>(system).getKineticEnergy();

  if (new_energy < previous_energy)
    return;

  const double probability =
    exp( - beta * (new_energy - previous_energy));

  static thread_local std::random_device device;
  static thread_local std::mt19937_64 generator(device());
  static thread_local std::uniform_real_distribution<double> distribution(0., 1.);

  if (distribution(generator) < probability)
    return;

  UndoStep();
}
