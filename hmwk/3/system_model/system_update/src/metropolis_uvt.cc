#include "metropolis_uvt.h"

MetropolisUVTUpdate::MetropolisUVTUpdate(ParticleSystem& system, double T, double U) :
  MetropolisUpdate(system), T(T), U(U) {}

void MetropolisUVTUpdate::RunUpdate() {}
