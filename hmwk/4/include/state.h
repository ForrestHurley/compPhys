#ifndef STATE_H
#define STATE_H

#include <memory>
#include <vector>

class State
{
private:
  std::vector<double> internal_state;

public:
  const int dimension;

  explicit State(int dimension);
  explicit State(const std::vector<double>& initial_state);

  static std::unique_ptr<State> RandomGaussian(
      double mean = 0., double standard_deviation = 1., int dimension = 1);

  double& at(int i);
  const double& at(int i) const;

  void setElement(int i, double element);
  double getElement(int i) const;

  double getDistanceSquared(const State& other) const;
  double getDistance(const State& other) const;
  double getDistanceFromOrigin() const;
};

#endif

