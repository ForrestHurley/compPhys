#include "metropolis_nvt.h"

MetropolisNVTUpdate::MetropolisNVTUpdate(ParticleSystem& system, double T) :
  MetropolisUpdate(system), T(T) {}

void MetropolisNVTUpdate::RunUpdate() {}
