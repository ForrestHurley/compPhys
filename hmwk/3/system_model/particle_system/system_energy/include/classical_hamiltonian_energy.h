#ifndef CLASSICAL_HAMILTONIAN_ENERGY_H
#define CLASSICAL_HAMILTONAIN_ENERGY_H

#include "diagonal_hamiltonian_energy.h"
#include "potential_energy.h"

class ClassicalHamiltonian : public DiagonalHamiltonian
{
private:
  const PotentialEnergy& potential;

public:
  ClassicalHamiltonian(const HamiltonianParticleState& state, const PotentialEnergy& potential);

  double MomentumPartial() override;
  double PositionPartial() override;

  double MomentumEnergy() override;
  double PositionEnergy() override;
};

#endif
