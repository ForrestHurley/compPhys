#ifndef HAMILTONIAN_ENERGY_H
#define HAMILTONIAN_ENERGY_H

#include "system_energy.h"

class HamiltonianEnergy : public SystemEnergy
{
public:
  HamiltonainEnergy(const HamiltonianState& state);

  virtual double MomentumPartial() = 0;
  virtual double PositionPartial() = 0;
};

#endif
