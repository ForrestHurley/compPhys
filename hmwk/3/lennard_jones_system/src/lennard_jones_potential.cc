#include "lennard_jones_potential.h"

LennardJonesPotential::LennardJonesPotential(
  double potential_depth, double maximum_potential_distance) :
  potential_depth(potential_depth),
  maximum_potential_distance(maximum_potential_distance) {}

double LennardJonesPotential::getPotential(
  const Coordinate& A, const Coordinate& B) const
{
  const double distance_squared = (A - B).getMagnitudeSquared();
  const double recip_squared =
    maximum_potential_distance * maximum_potential_distance / distance_squared;
  
  const double sixth_pow = recip_squared * recip_squared * recip_squared;
  const double twelth_pow = sixth_pow * sixth_pow;

  const double potential = 
    4 * potential_depth * (twelth_pow - sixth_pow);
  return potential;
}

Coordinate LennardJonesPotential::getPartials(
  const Coordinate& A, const Coordinate& B) const
{
  const Coordinate displacement = B - A;
  const Coordiante unit_displacement = displacement.getNormalized();

  const double distance_squared = displacement.getMagnitudeSquared();
  const double distance = sqrt(distance_squared);

  const double recip_squared =
    maximum_potential_distance * maximum_potential_distance / distance_squared;
  
  const double sixth_pow = recip_squared * recip_squared * recip_squared;
  const double twelth_pow = sixth_pow * sixth_pow;

  // 4 * e * (6 * p^6 / r^7 - 12 * p^12 / r^13)
  const double derivative = 
    4 * potential_depth * (6 * sixth_pow - 12 * twelth_pow) / distance;

  const Coordinate partial_derivatives =
    unit_displacement * derivative;

  return partial_derivatives;
}

