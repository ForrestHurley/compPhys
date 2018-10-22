#ifndef ENERGY_LOGGER_H
#define ENERGY_LOGGER_H

#include "data_logger.h"
#include <vector>

class EnergyLogger final : public DataLogger
{
private:
  std::vector<double> energies;
  std::vector<double> times;

public:
  EnergyLogger(const ParticleSystem& system);

  void Log(double current_time) override;
  int getLogCount() const override;

  friend std::ostream& operator<<(
    std::ostream &os, const EnergyLogger &logger);
};

#endif
