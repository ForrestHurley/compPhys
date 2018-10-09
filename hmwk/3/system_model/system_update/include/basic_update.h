#ifndef BASIC_UPDATE_H
#define BASIC_UPDATE_H

#include "particle_system.h"

class BasicUpdate
{
protected:
  ParticleSystem& system;
public:
  BasicUpdate(ParticleSystem& system);

  virtual void RunUpdate() = 0;
  virtual void RunUpdateN(int total_steps);
  virtual void RunUpdateForDuration(double total_time);
};

#endif
