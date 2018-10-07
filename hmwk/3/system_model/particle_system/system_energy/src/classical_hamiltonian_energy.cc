#include "classical_hamiltonian_energy.h"

ClassicalHamiltonian::ClassicalHamiltonian(const HamiltonianParticleState& state, const PotentialEnergy& potential) :
  DiagonalHamiltonian(state), potential(potential) {}

double ClassicalHamiltonian::MomentumPartial()
{
  return 0.;
}

double ClassicalHamiltonian::PositionPartial()
{
  return 0.;
}

double ClassicalHamiltonian::MomentumEnergy()
{
  return 0.;
}

double ClassicalHamiltonian::PositionEnergy()
{
  return 0.;
}
