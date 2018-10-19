#include "classical_hamiltonian_energy.h"

ClassicalHamiltonian::ClassicalHamiltonian(const HamiltonianParticleState& state, const PotentialEnergy& potential) :
  DiagonalHamiltonian(state), potential(potential) {}

std::vector<Coordinate> ClassicalHamiltonian::MomentumPartial() const
{
  const HamiltonianParticleState& hamiltonian_state =
    static_cast<const HamiltonianParticleState&>(state);
  const std::vector<SmoothCoordinateSpace::SmoothCoordinatePoint*>& momenta =
    hamiltonian_state.getMomenta();

  std::vector<Coordinate> partial_derivatives;
  partial_derivatives.reserve(momenta.size());

  //The partial derivative of H is just p/m (or p if m == 1)
  for (int i = 0; i < momenta.size(); i++)
    partial_derivatives.push_back(momenta.at(i)->getCoordinate());  

  return partial_derivatives;
}

std::vector<Coordinate> ClassicalHamiltonian::PositionPartial() const
{
  return potential.getPartials();
}

double ClassicalHamiltonian::MomentumEnergy() const
{
  double energy = 0.;

  for (SmoothCoordinateSpace::SmoothCoordinatePoint* coordinate_point : 
    static_cast<const HamiltonianParticleState&>(state).getMomenta())
  {
    //Assuming mass = 1, p^2/(2m)
    energy += coordinate_point->getCoordinate().getMagnitudeSquared() * 0.5;
  }

  return energy;
}

double ClassicalHamiltonian::PositionEnergy() const
{
  return potential.getPotentialEnergy();
}
