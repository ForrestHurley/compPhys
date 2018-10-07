#ifndef HAMILTONIAN_ENERGY_H
#define HAMILTONIAN_ENERGY_H

#include "system_energy.h"
#include "hamiltonian_particle_state.h"

class HamiltonianEnergy : public SystemEnergy
{
public:
  HamiltonianEnergy(const HamiltonianParticleState& state);

  virtual double MomentumPartial() = 0;
  virtual double PositionPartial() = 0;
};

#endif
