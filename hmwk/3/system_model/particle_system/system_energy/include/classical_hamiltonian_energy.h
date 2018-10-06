#ifndef CLASSICAL_HAMILTONIAN_ENERGY_H
#define CLASSICAL_HAMILTONAIN_ENERGY_H

class ClassicalHamiltonian : public DiagonalHamiltonian
{
private:
  const PotentialEnergy& potential;

public:
  ClassicalHamiltonian(const HamiltonianState& state, const PotentialEnergy& potential);

  double MomentumPartial() override;
  double PositionPartial() override;

  double MomentumEnergy() override;
  double PositionEnergy() override;
};

#endif
