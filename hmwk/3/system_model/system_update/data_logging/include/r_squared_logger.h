#ifndef R_SQUARED_LOGGER_H
#define R_SQUARED_LOGGER_H

#include "data_logger.h"
#include "hamiltonian_particle_system.h"
#include "displacement_logger.h"
#include <vector>

class RSquaredLogger final : public DataLogger
{
private:
  DisplacementLogger& displacement_logger;
  const bool owns_displacement_logger;

  std::vector<std::vector<Coordinate> > displacement_magnitude_squared;
  std::vector<double> time;

public:
  RSquaredLogger(const HamiltonianParticleSystem& system);
  RSquaredLogger(const DisplacementLogger& displacement_logger);
  ~RSquaredLogger();

  void Log(double current_time) override;
  int getLogCount() const override;

  friend std::ostream& operator<<(
    std::ostream &os, const RSquaredLogger &logger);
  
};

#endif
