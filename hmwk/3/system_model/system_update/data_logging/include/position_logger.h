#ifndef POSITION_LOGGER_H
#define POSITION_LOGGER_H

#include "data_logger.h"
#include <vector>
#include "hamiltonian_particle_system.h"

class PositionLogger : public DataLogger
{
private:
  std::vector< std::vector<Coordinate> > positions;
  std::vector<double> times;

public:
  PositionLogger(const HamiltonianParticleSystem& system);

  void Log(double current_time) override;
  int getLogCount() const override;

  friend std::ostream& operator<<(
    std::ostream &os, const PositionLogger &logger);
};

#endif