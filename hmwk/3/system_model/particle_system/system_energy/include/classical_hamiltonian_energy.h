#ifndef CLASSICAL_HAMILTONIAN_ENERGY_H
#define CLASSICAL_HAMILTONIAN_ENERGY_H

#include "diagonal_hamiltonian_energy.h"
#include "potential_energy.h"

class ClassicalHamiltonian : public DiagonalHamiltonian
{
private:
  const PotentialEnergy& potential;

public:
  ClassicalHamiltonian(const HamiltonianParticleState& state, const PotentialEnergy& potential);

  std::vector<Coordinate> MomentumPartial() const override;
  std::vector<Coordinate> PositionPartial() const override;

  double MomentumEnergy() const override;
  double PositionEnergy() const override;
};

#endif
