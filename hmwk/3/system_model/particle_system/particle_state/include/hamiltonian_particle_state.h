#ifndef HAMILTONIAN_PARTICLE_STATE_H
#define HAMILTONIAN_PARTICLE_STATE_H

#include "particle_state.h"
#include "smooth_coordinate_space.h"

class HamiltonianParticleState : public ParticleState
{
public:
  HamiltonianParticleState();

  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& getPositions() const;
  void setPositions(const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& new_positions);

  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& getMomenta() const;
  void setMomenta(const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& new_momenta);
};

#endif
