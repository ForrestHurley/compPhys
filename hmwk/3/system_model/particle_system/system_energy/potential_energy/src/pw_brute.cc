#include "pw_brute.h"

PairwiseBruteForcePotentialEnergy::PairwiseBruteForcePotentialEnergy(
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& locations,
  const PairwisePotentialFunction& pairwise_potential) :
  PairwisePotentialEnergy(locations, pairwise_potential) {}

double PairwiseBruteForcePotentialEnergy::getPotentialEnergy() const
{
  double energy = 0.;

  for (int i = 0; i < locations.size(); i++)
  {
    const SmoothCoordinateSpace* space = locations.at(i)->getSpace();
    for (int j = i + 1; j < locations.size(); j++)
    {
      assert(space == locations.at(j)->getSpace());

      //Multiply by two becaus the potential is from the perspective of a single particle
      energy += 2 * pairwise_potential.getPotential(
        space->Distance(
          *locations.at(i), *locations.at(j)));
    }
  }

  return energy;
}

std::vector<Coordinate> PairwiseBruteForcePotentialEnergy::getPartials() const
{
  std::vector<Coordinate> partial_derivatives;
  partial_derivatives.reserve(locations.size());

  //Initialize the partial derivative vector
  for (
    SmoothCoordinateSpace::SmoothCoordinatePoint* particle_location : locations)
    partial_derivatives.push_back(Coordinate::Zero(particle_location->getDimension()));

  for(int i = 0; i < locations.size(); i++)
  {
    const SmoothCoordinateSpace* space = locations.at(i)->getSpace();
    for (int j = 0; j < locations.size(); j++)
    {
      assert(space == locations.at(j)->getSpace());

      partial_derivatives.at(i) =
        partial_derivatives.at(i) +
        pairwise_potential.getPartials(
          space->DisplacementVector(
            *locations.at(i), *locations.at(j)));
    }
  }

  return partial_derivatives;
}

