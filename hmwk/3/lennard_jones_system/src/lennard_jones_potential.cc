#include "lennard_jones_potential.h"
#include <iostream>

LennardJonesPotential::LennardJonesPotential(
  double potential_depth, double maximum_potential_distance) :
  potential_depth(potential_depth),
  maximum_potential_distance(maximum_potential_distance) {}

double LennardJonesPotential::getPotential(
  double distance) const
{
  //const double distance_squared = distance * distance;
  const double recip =
    maximum_potential_distance / distance;
  const double recip_squared = recip * recip;

  const double sixth_pow = recip_squared * recip_squared * recip_squared;
  const double twelth_pow = sixth_pow * sixth_pow;

  const double potential = 
    4 * potential_depth * (twelth_pow - sixth_pow);
  return potential;
}

Coordinate LennardJonesPotential::getPartials(
  const Coordinate& displacement) const
{
  Coordinate unit_displacement = displacement.getNormalized();

  const double distance_squared = displacement.getMagnitudeSquared();
  const double distance = sqrt(distance_squared);

  const double recip_squared =
    maximum_potential_distance * maximum_potential_distance / distance_squared;
  
  const double sixth_pow = recip_squared * recip_squared * recip_squared;
  const double twelth_pow = sixth_pow * sixth_pow;

  // 4 * e * (6 * p^6 / r^7 - 12 * p^12 / r^13)
  const double derivative = 
    4 * potential_depth * (6 * sixth_pow - 12 * twelth_pow) / distance;

  unit_displacement *= derivative;
  
  /*for (double val : partial_derivatives.asVector())
    std::cout << val << "|";
  std::cout << std::endl;*/

  return unit_displacement;
}

