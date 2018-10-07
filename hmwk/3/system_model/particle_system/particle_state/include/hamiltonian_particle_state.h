#ifndef HAMILTONIAN_PARTICLE_STATE_H
#define HAMILTONIAN_PARTICLE_STATE_H

#include "particle_state.h"

class HamiltonianParticleState : public ParticleState
{
public:
  HamiltonianParticleState();

  std::vector<Coordinate> getPositions();
  void setPositions(std::vector<Coordinate> new_positions);

  std::vector<Coordinate> getMomenta();
  void setMomenta(std::vector<Coordinate> new_momenta);
};

#endif
