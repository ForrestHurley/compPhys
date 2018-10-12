#include "metropolis_npt.h"

MetropolisNPTUpdate::MetropolisNPTUpdate(ParticleSystem& system, double T, double P) :
  MetropolisUpdate(system), T(T), P(P) {}

void MetropolisNPTUpdate::RunUpdate() {}
