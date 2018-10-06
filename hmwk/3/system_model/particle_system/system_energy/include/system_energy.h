#ifndef SYSTEM_ENERGY_H
#define SYSTEM_ENERGY_H

class SystemEnergy
{
protected:
  const ParticleState& state;

public:
  SystemEnergy(const ParticleState& state);

  virtual double Energy() = 0;
};

#endif
