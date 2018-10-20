#ifndef PARTICLE_STATE_H
#define PARTICLE_STATE_H

#include <vector>
#include "coordinate.h"
#include "smooth_coordinate_space.h"

class ParticleState
{
protected:
  std::vector< std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> > state;
  std::vector< SmoothCoordinateSpace* > coordinate_spaces;
public:
  ParticleState(const std::vector<SmoothCoordinateSpace* >& coordinate_spaces);
  virtual ~ParticleState();

  void AddOriginParticle();
  void AddParticle(const std::vector<Coordinate>& particle_state);

  const std::vector< std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*> >& getState() const;
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& getStateComponent(int component_number) const;
};

#endif
