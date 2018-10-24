#ifndef HAMILTONIAN_PARTICLE_STATE_H
#define HAMILTONIAN_PARTICLE_STATE_H

#include "particle_state.h"
#include "smooth_coordinate_space.h"

class HamiltonianParticleState : public ParticleState
{
public:
  HamiltonianParticleState(
    SmoothCoordinateSpace* position_space,
    SmoothCoordinateSpace* momentum_space);

  void AddParticle(
    const Coordinate& position,
    const Coordinate& momentum);
  void AddStationaryParticle(
    const Coordinate& position);

  SmoothCoordinateSpace* getPositionSpace() const;
  SmoothCoordinateSpace* getMomentumSpace() const;

  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& getPositions() const;
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& getMomenta() const;
};

#endif
