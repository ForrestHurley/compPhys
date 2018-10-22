#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include "particle_system.h"
#include <iostream>

class DataLogger
{
protected:
  const ParticleSystem& system;
public:
  DataLogger(const ParticleSystem& system);
  virtual ~DataLogger() {}

  virtual void Log(double current_time) = 0;
  virtual int getLogCount() const = 0;
};

#endif
