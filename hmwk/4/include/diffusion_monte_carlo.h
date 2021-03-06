#ifndef DIFFUSION_MONTE_CARLO_H
#define DIFFUSION_MONTE_CARLO_H

#include "diffusion.h"
#include <vector>

class DiffusionMonteCarlo : public Diffusion
{
private:
  double nucleus_count;
  int electron_count;
  int goal_walker_count;
  double energy_guess;
  double energy_t;
  int geometric_dimension;

  std::vector<double> calculated_energies;

  void CalculatePotential(State& walker_state) const;
  void UpdateCalculatedEnergies();

protected:
  virtual void addDiffusion(State& walker_state, double time_step) const override;
  virtual void addDrift(State& walker_state, double time_step) const override;
  virtual int getProliferation(
      State& walker_state, 
      double time_step) const override;

  virtual void PostIteration() override;

public:
  explicit DiffusionMonteCarlo(
      double nucleus_count,
      int electron_count,
      double energy_guess = 0.,
      int dimension = 3,
      int initial_walker_count = 1000);

  double getCalculatedEnergy() const;
  const std::vector<double>& getPastCalculatedEnergies() const;
  void ClearCalculatedEnergies();
};

#endif
