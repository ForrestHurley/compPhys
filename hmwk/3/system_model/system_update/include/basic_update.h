#ifndef BASIC_UPDATE_H
#define BASIC_UPDATE_H

#include "particle_system.h"
#include <vector>
#include "data_logger.h"

class BasicUpdate
{
private:
  std::vector<DataLogger*> logger_list;

protected:
  ParticleSystem& system;

  virtual void SetupUpdate() {};
  virtual void RunUpdate() = 0;

public:
  BasicUpdate(ParticleSystem& system);

  void RunUpdateN(int total_steps, bool verbose = false);
  void RunUpdateForDuration(double total_time);

  void addLogger(DataLogger* logger);

  template< class MetropolisType>
  friend class MetropolisDynamicsUpdate;
};

#endif
