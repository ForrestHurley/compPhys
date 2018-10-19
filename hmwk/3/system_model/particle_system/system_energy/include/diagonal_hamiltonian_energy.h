#ifndef DIAGONAL_HAMILTONIAN_ENERGY_H
#define DIAGONAL_HAMILTONIAN_ENERGY_H

#include "hamiltonian_energy.h"

class DiagonalHamiltonian : public HamiltonianEnergy
{
public:
  DiagonalHamiltonian(const HamiltonianParticleState& state);

  double Energy() const override;
  
  virtual double MomentumEnergy() const = 0;
  virtual double PositionEnergy() const = 0;
};

#endif
