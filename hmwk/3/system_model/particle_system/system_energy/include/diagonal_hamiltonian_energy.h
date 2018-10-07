#ifndef DIAGONAL_HAMILTONIAN_ENERGY_H
#define DIAGONAL_HAMILTONIAN_ENERGY_H

#include "hamiltonian_energy.h"

class DiagonalHamiltonian : public HamiltonianEnergy
{
public:
  DiagonalHamiltonian(const HamiltonianParticleState& state);

  double Energy() override;
  
  virtual double MomentumEnergy() = 0;
  virtual double PositionEnergy() = 0;
};

#endif
