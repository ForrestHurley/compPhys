#ifndef HAMILTONIAN_ENERGY_H
#define HAMILTONIAN_ENERGY_H

#include "system_energy.h"
#include "hamiltonian_particle_state.h"

class HamiltonianEnergy : public SystemEnergy
{
public:
  HamiltonianEnergy(const HamiltonianParticleState& state);

  virtual std::vector<Coordinate> MomentumPartial() const = 0;
  virtual std::vector<Coordinate> PositionPartial() const = 0;
};

#endif
