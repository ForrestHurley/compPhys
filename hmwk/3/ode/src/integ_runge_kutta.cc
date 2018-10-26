
#include "integ_runge_kutta.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <assert.h>

RungeKuttaIntegrator::RungeKuttaIntegrator(bool flatten_input_state) :
  ODESolver(flatten_input_state) {}

RungeKuttaIntegrator::RungeKuttaIntegrator(
  ODEInterface *differential_equation, bool flatten_input_state) : 
  ODESolver(differential_equation, flatten_input_state) {}

std::vector< std::vector<double> > RungeKuttaIntegrator::CalculateFullDerivative(
  std::vector< std::vector<double> > state, double time)
{
  std::vector<double> highest_deriv =
    differential_equation->CalculateHighestDerivative(state, time);

  //for (double val : highest_deriv) std::cout << val << "$";
  //std::cout << std::endl;

  for (int i = 0; i < state.size(); i++)
  {
    std::rotate(state.at(i).begin(),
      state.at(i).begin() + 1,
      state.at(i).end());
    state.at(i).at(state.at(i).size() - 1) = highest_deriv.at(i);
  }

  return state;
}

void RungeKuttaIntegrator::multiply(std::vector< std::vector<double> > &vect, double scalar)
{
  for (int i = 0; i < vect.size(); i++)
    for (int j = 0; j < vect.at(i).size(); j++)
      vect.at(i).at(j) *= scalar;
}

void RungeKuttaIntegrator::add(std::vector< std::vector<double> > &A,
  const std::vector< std::vector<double> > &B)
{
  assert(A.size() == B.size());
  for (int i = 0; i < A.size(); i++)
  {
    assert(A.at(i).size() == B.at(i).size());
    for (int j = 0; j < A.at(i).size(); j++)
      A.at(i).at(j) += B.at(i).at(j);
  }
}

void RungeKuttaIntegrator::StepState(double time_step, double time)
{
  std::vector< std::vector<double> > k1, k2, k3, k4;
  k1.reserve(state.size());
  k2.reserve(state.size());
  k3.reserve(state.size());
  k4.reserve(state.size());

  std::vector< std::vector<double> > tmp_derivs;
  std::vector< std::vector<double> > tmp_state;
  std::vector< std::vector<double> > tmp_k;

  //Calculate k1
  tmp_derivs = CalculateFullDerivative(state, time);
  /*for (std::vector<double> row : tmp_derivs)
  {
    for (double val : row) std::cout << val << ",";
    std::cout << std::endl;
  }*/

  k1 = tmp_derivs;
  multiply(k1, time_step);
  
  //Calculate k2
  tmp_k = k1;
  multiply(tmp_k, 0.5);
  tmp_state = state;
  add(tmp_state, tmp_k);
  tmp_derivs = CalculateFullDerivative(tmp_state, time + time_step * 0.5);
  k2 = tmp_derivs;
  multiply(k2, time_step);

  //Calculate k3
  tmp_k = k2;
  multiply(tmp_k, 0.5);
  tmp_state = state;
  add(tmp_state, tmp_k);
  tmp_derivs = CalculateFullDerivative(tmp_state, time + time_step * 0.5);
  k3 = tmp_derivs;
  multiply(k3, time_step);

  //Calculate k4
  tmp_state = state;
  add(tmp_state, k3);
  tmp_derivs = CalculateFullDerivative(tmp_state, time + time_step);
  k4 = tmp_derivs;
  multiply(k4, time_step);

  //Calculate new state
  for (unsigned int i = 0; i < state.size(); i++)
  {
    for (unsigned int j = 0; j < state.at(i).size(); j++)
    {
      state.at(i).at(j) += 1. / 6. * 
        (k1.at(i).at(j) + 2. * k2.at(i).at(j) + 2. * k3.at(i).at(j) + k4.at(i).at(j));
      //std::cout << state.at(i).at(j) << "|";
    }
    //std::cout << ":";
  }
  //std::cout << std::endl;
}
