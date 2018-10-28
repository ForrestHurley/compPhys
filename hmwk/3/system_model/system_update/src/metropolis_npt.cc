#include "metropolis_npt.h"

MetropolisNPTUpdate::MetropolisNPTUpdate(ClassicalParticleSystem& system, double T, double P) :
  MetropolisUpdate(system), T(T), P(P) {}

void MetropolisNPTUpdate::RunUpdate() {}
