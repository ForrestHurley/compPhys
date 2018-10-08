#ifndef HAMILTONIAN_PARTICLE_STATE_H
#define HAMILTONIAN_PARTICLE_STATE_H

#include "particle_state.h"
#include "smooth_coordinate_space.h"

class HamiltonianParticleState : public ParticleState
{
public:
  HamiltonianParticleState();

  std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> getPositions() const;
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& getPositionReference() const;
  void setPositions(std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> new_positions);

  std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> getMomenta() const;
  void setMomenta(std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> new_momenta);
};

#endif
