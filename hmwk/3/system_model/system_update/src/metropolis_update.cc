#include "metropolis_update.h"
#include "hamiltonian_particle_state.h"

MetropolisUpdate::MetropolisUpdate(ClassicalParticleSystem& system, double mean_squared_step, int zero_momentum_interval) :
  BasicUpdate(system), mean_squared_step(mean_squared_step), zero_momentum_interval(zero_momentum_interval) {}

void MetropolisUpdate::setMeanSquaredStep(double new_step_size) { mean_squared_step = new_step_size; }
double MetropolisUpdate::getMeanSquaredStep() const { return mean_squared_step; }

void MetropolisUpdate::setZeroMomentumInterval(int new_interval) { zero_momentum_interval = new_interval; }
int MetropolisUpdate::getZeroMomentumInterval() const { return zero_momentum_interval; }

void MetropolisUpdate::RandomStep()
{
  HamiltonianParticleState& hamiltonian_state =
    static_cast<HamiltonianParticleState&>(system.getState());

  std::vector<Coordinate> new_velocities;
  const int dimension = hamiltonian_state.getMomentumSpace()->getDimension();

  static thread_local std::random_device device;
  static thread_local std::mt19937_64 generator(device());

  for (SmoothCoordinateSpace::SmoothCoordinatePoint* point : hamiltonian_state.getMomenta())
  {
    Coordinate random_step = Coordinate::RandomGaussian(dimension, generator);
    random_step *= mean_squared_step;
    random_step += point->getCoordinate();
    new_velocities.push_back(random_step);
  }

  MakeStep(new_velocities);
}

void MetropolisUpdate::MakeStep(const std::vector<Coordinate>& new_velocities)
{
  const HamiltonianParticleState& hamiltonian_state =
    static_cast<HamiltonianParticleState&>(system.getState());
  Coordinate total_velocity = Coordinate::Zero(
    hamiltonian_state.getMomentumSpace()->getDimension());
  steps_since_last_momentum_reset++;

  last_velocities.clear();
  unsigned int index = 0;
  for (SmoothCoordinateSpace::SmoothCoordinatePoint* point :
    hamiltonian_state.getMomenta())
  {
    last_velocities.push_back(point->getCoordinate());
    point->setCoordinate(new_velocities.at(index++));

    if (steps_since_last_momentum_reset == zero_momentum_interval)
    {
      total_velocity += point->getCoordinate();
    }
  }

  assert(index == new_velocities.size());

  //Zero the total velocity of the system
  if (steps_since_last_momentum_reset == zero_momentum_interval)
  {
    steps_since_last_momentum_reset = 0;
    total_velocity /= hamiltonian_state.getMomenta().size();

    for (SmoothCoordinateSpace::SmoothCoordinatePoint* point :
      hamiltonian_state.getMomenta())
    {
      point->setCoordinate(
        point->getCoordinate() - total_velocity);
    }
  }
}

void MetropolisUpdate::UndoStep()
{
  unsigned int index = 0;
  for (SmoothCoordinateSpace::SmoothCoordinatePoint* point :
    static_cast<HamiltonianParticleState&>(system.getState()).getMomenta())
  {
    point->setCoordinate(last_velocities.at(index++));
  }
}
