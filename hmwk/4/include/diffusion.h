#ifndef DIFFUSION_H
#define DIFFUSION_H

#include "state.h"
#include <list>
#include <vector>
#include <memory>

class DiffusionInterface
{
public:
  void RunIterations(int number of iterations, double time_step) = 0;
};

class Diffusion : public DiffusionInterface
{
private:
  std::list<state> walkers;
  int initial_walker_count;

  double diffusion_constant = 1.;
  double drift_constant = 0.;

protected:
  virtual void addDiffusion(state& walker_state, double time_step) const;
  virtual void addDrift(state& walker_state, double time_step) const;
  virtual int getProliferation(
      state& walker_state,
      double time_step) const;

  virtual void PostIteration() {};

  virtual std::unique_ptr<state> getRandomInitialState() const;

  double getRandomGaussian(double mean = 0., double standard_deviation = 1.) const;

public:
  const int dimension;

  explicit Diffusion(int initial_walker_count = 1000, int dimension = 1);
  explicit Diffusion(const std::vector<state>& initial_walkers);
  explicit Diffusion(const std::list<state>& initial_walkers);

  void RunIterations(int number_of_iterations, double time_step = 0.01) override;

  const std::list<state>& getWalkers() const;
  int getWalkerCount() const;

  void setInitialWalkers(const std::vector<state>& initial_walkers);
  void setInitialWalkers(const std::list<state>& initial_walkers);
  void RegenerateWalkers();
  void RegenerateNWalkers(int walker_count);

  void setDiffusionConstant(double diffusion_constant);
  double getDiffusionConstant();

  void setDriftConstant(double drift_constant);
  double getDriftConstant();
};

#endif
