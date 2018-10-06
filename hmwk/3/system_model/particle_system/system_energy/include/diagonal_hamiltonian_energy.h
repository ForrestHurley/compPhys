#ifndef DIAGONAL_HAMILTONIAN_ENERGY_H
#define DIAGONAL_HAMILTONIAN_ENERGY_H

class DiagonalHamiltonian : public HamiltonianEnergy
{
public:
  DiagonalHamiltonian(const HamiltonianState& state);

  double Energy() override;
  
  virtual double MomentumEnergy() = 0;
  virtual double PositionEnergy() = 0;
};

#endif
