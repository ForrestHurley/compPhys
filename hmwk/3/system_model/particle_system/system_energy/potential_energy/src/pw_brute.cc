#include "pw_brute.h"
#include <iostream>

PairwiseBruteForcePotentialEnergy::PairwiseBruteForcePotentialEnergy(
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& locations,
  const PairwisePotentialFunction& pairwise_potential) :
  PairwisePotentialEnergy(locations, pairwise_potential) {}

double PairwiseBruteForcePotentialEnergy::getPotentialEnergy() const
{
  double energy = 0.;

  const SmoothCoordinateSpace* space = locations.at(0)->getSpace();
  for (int i = 1; i < locations.size(); i++)
      assert(space == locations.at(i)->getSpace());

  for (int i = 0; i < locations.size(); i++)
  {
    for (int j = i + 1; j < locations.size(); j++)
    {
      //Multiply by two becaus the potential is from the perspective of a single particle
      energy += pairwise_potential.getPotential(
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

  const SmoothCoordinateSpace* space = locations.at(0)->getSpace();
  for (int i = 1; i < locations.size(); i++)
      assert(space == locations.at(i)->getSpace());

  for(int i = 0; i < locations.size(); i++)
  {
    for (int j = 0; j < locations.size(); j++)
    {
      if (i == j)
        continue;

      //TODO: add something to deal with NaN
      partial_derivatives.at(i) +=
        pairwise_potential.getPartials(
          space->DisplacementVector(
            *locations.at(i), *locations.at(j)));
    }
  }

  return partial_derivatives;
}

