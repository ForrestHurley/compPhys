
#include "displacement_logger.h"
#include <assert.h>

DisplacementLogger::DisplacementLogger(
  const HamiltonianParticleSystem& system) :
  DataLogger(system) {}

void DisplacementLogger::Log(double current_time)
{
  times.push_back(current_time);

  const HamiltonianParticleState& state =
    static_cast<const HamiltonianParticleSystem&>(system)
    .getCurrentState();

  SmoothCoordinateSpace* space =
    state.getPositionSpace();

  if (last_positions.size() > 0)
  {
    assert(last_positions.size() == 
      state.getPositions().size());

    std::vector<Coordinate> temp_displacement;
    std::vector<Coordinate> temp_total = total_displacements.at(
      total_displacements.size() - 1);
    for (int i = 0; i < state.getPositions().size(); i++)
    {
      const Coordinate disp = 
        space->DisplacementVector(
          *state.getPositions().at(i),
          *last_positions.at(i));

      temp_displacement.push_back(disp);
      temp_total.at(i) = temp_total.at(i) + disp;
    }

    displacements.push_back(temp_displacement);
    total_displacements.push_back(temp_total);
  }
  else
  {
    total_displacements.push_back(
      std::vector<Coordinate>(
        state.getPositions().size(), 
        Coordinate::Zero(space->getDimension())));
  }

  for (SmoothCoordinateSpace::SmoothCoordinatePoint* particle :
    last_positions)
    state.getPositionSpace()
    ->DestroyPoint(particle);
  last_positions.clear();

  for (SmoothCoordinateSpace::SmoothCoordinatePoint* particle :
      state.getPositions())
  {
    last_positions.push_back(
      &state.getPositionSpace()
      ->CreatePoint(particle->getCoordinate()));
  }
}

int DisplacementLogger::getLogCount() const
{
  return times.size();
}

std::ostream& operator<<(
  std::ostream &os, const DisplacementLogger &logger)
{

}
