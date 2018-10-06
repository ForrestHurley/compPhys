#ifndef PAIRWISE_POTENTIAL_ENERGY_H
#define PAIRWISE_POTENTIAL_ENERGY_H

#include "potential_energy.h"
#include "pairwise_potential_function.h"
#include "metric_potential.h"

class PairwisePotentialEnergy : public PotentialEnergy
{
protected:
  const PairwisePotentialFunction& pairwise_potential;
public:
  PairwisePotentialEnergy(const std::vector<MetricSpace::MetricPoint*>& locations, const PairwisePotentialFunction& pairwise_potential);  
};

#endif
