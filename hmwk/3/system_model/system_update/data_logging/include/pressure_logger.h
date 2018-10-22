#ifndef PRESSURE_LOGGER_H
#define PRESSURE_LOGGER_H

#include "data_logger.h"
#include "classical_particle_system.h"
#include <vector>

class PressureLogger final : public DataLogger
{
private:
  std::vector<double> pressure;
  std::vector<double> time;

public:
  PressureLogger(const ClassicalParticleSystem& system);

  void Log(double current_time) override;
  int getLogCount() const override;

  friend std::ostream& operator<<(
    std::ostream &os, const PressureLogger &logger);
};

#endif
