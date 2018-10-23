#ifndef VELOCITY_LOGGER_H
#define VELOCITY_LOGGER_H

#include "data_logger.h"
#include <vector>
#include "hamiltonian_particle_system.h"

class VelocityLogger : public DataLogger
{
private:
  std::vector<std::vector<Coordinate> > velocities;
  std::vector<double> times;

public:
  VelocityLogger(const HamiltonianParticleSystem& system);

  void Log(double current_time) override;
  int getLogCount() const override;

  friend std::ostream& operator<<(
    std::ostream &os, const VelocityLogger &logger);

};

#endif
