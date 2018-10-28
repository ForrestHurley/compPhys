#include "metropolis_uvt.h"

MetropolisUVTUpdate::MetropolisUVTUpdate(ClassicalParticleSystem& system, double T, double U) :
  MetropolisUpdate(system), T(T), U(U) {}

void MetropolisUVTUpdate::RunUpdate() {}
