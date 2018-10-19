#include "pw_brute.h"

PairwiseBruteForcePotentialEnergy::PairwiseBruteForcePotentialEnergy(
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& locations,
  const PairwisePotentialFunction& pairwise_potential) :
  PairwisePotentialEnergy(locations, pairwise_potential) {}

double PairwiseBruteForcePotentialEnergy::getPotentialEnergy()
{
  double energy = 0.;

  for (int i = 0; i < locations.size(); i++)
  {
    for (int j = i + 1; j < locations.size(); j++)
    {
      //Multiply by two becaus the potential is from the perspective of a single particle
      energy += 2 * pairwise_potential.getPotential(
        locations.at(i)->getCoordinate(),
        locations.at(j)->getCoordinate());
    }
  }

  return energy;
}

std::vector<Coordinate> PairwiseBruteForcePotentialEnergy::getPartials()
{
  std::vector<Coordinate> partial_derivatives;
  partial_derivatives.reserve(locations.size());

  //Initialize the partial derivative vector
  for (
    SmoothCoordinateSpace::SmoothCoordinatePoint* particle_location : locations)
    partial_derivatives.push_back(Coordinate::Zero(particle_location->dimension));

  for(int i = 0; i < locations.size(); i++)
  {
    for (int j = 0; j < locations.size(); j++)
    {
      partial_derivatives.at(i) =
        partial_derivatives.at(i) +
        pairwise_potential.getPartials(
          locations.at(i)->getCoordinate(),
          locations.at(j)->getCoordinate());
    }
  }

  return partial_derivatives;
}

