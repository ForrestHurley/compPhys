#include "diagonal_hamiltonian_energy.h"

DiagonalHamiltonian::DiagonalHamiltonian(const HamiltonianParticleState& state) : HamiltonianEnergy(state) {}

double DiagonalHamiltonian::Energy()
{
  return 0.;
}
