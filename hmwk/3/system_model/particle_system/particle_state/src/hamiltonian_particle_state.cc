#include "hamiltonian_particle_state.h"

HamiltonianParticleState::HamiltonianParticleState() {}

std::vector<Coordinate> HamiltonianParticleState::getPositions()
{
  return getStateComponent(0);
}

void HamiltonianParticleState::setPositions(std::vector<Coordinate> new_positions) {}

std::vector<Coordinate> HamiltonianParticleState::getMomenta()
{
  return getStateComponent(1);
}

void HamiltonianParticleState::setMomenta(std::vector<Coordinate> new_momenta) {} 
