#ifndef CLASSICAL_PAIRWISE_PARTICLE_SYSTEM_H
#define CLASSICAL_PAIRWISE_PARTICLE_SYSTEM_H

#include "classical_particle_system.h"
#include "pairwise_potential_function.h"
#include "pairwise_potential_energy.h"
#include "pw_brute.h"

class ClassicalPairwiseParticleSystem : public ClassicalParticleSystem
{
private:
  PairwiseBruteForcePotentialEnergy pairwise_potential_energy;
public:
  ClassicalPairwiseParticleSystem(
    const PairwisePotentialFunction& pairwise_potential,
    HamiltonianParticleState& initial_state);
};

#endif
