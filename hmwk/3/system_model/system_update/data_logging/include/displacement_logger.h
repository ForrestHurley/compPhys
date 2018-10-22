#ifndef DISPLACEMENT_LOGGER_H
#define DISPLACEMENT_LOGGER_H

#include "data_logger.h"
#include "hamiltonian_particle_system.h"
#include <vector>

class DisplacementLogger final : public DataLogger
{
private:
  std::vector<std::vector<Coordinate> > displacement;
  std::vector<double> time;

public:
  DisplacementLogger(const HamiltonianParticleSystem& system);

  void Log(double current_time) override;
  int getLogCount() const override;

  friend std::ostream& operator<<(
    std::ostream &os, const DisplacementLogger &logger);

  friend class RSquaredLogger;
};

#endif

