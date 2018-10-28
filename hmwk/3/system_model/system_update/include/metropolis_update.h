#ifndef METROPOLIS_UPDATE_H
#define METROPOLIS_UPDATE_H

#include "basic_update.h"
#include "classical_particle_system.h"

class MetropolisUpdate : public BasicUpdate
{
private:
  std::vector<Coordinate> last_velocities;
  double mean_squared_step;
  int zero_momentum_interval;
  int steps_since_last_momentum_reset = 0;

protected:
  virtual void RandomStep();
  void MakeStep(const std::vector<Coordinate>& new_velocities);
  void UndoStep();
public:
  MetropolisUpdate(ClassicalParticleSystem& system, double mean_squared_step = 0.1, int zero_momentum_interval = 1);

  void setMeanSquaredStep(double new_step_size);
  double getMeanSquaredStep() const;

  void setZeroMomentumInterval(int new_interval);
  int getZeroMomentumInterval() const;
};

#endif
