#include "expected_chain_value.h"

void average_chains::norm_prob(std::vector<mpfr::mpreal>& in_probs)
{
  //kahan summation algorithm
  mpfr::mpreal sum, y, t, c;
  sum = c = 0.;
  for (mpfr::mpreal& val : in_probs)
  {
    y = val - c;
    t = sum + y;
    c = (t - sum) - y;
    sum = t;
  }

  //normalize sum to 1
  for (mpfr::mpreal& val : in_probs)
    val /= sum;
}

void average_chains::add_chain(std::vector<double> y, std::vector<double> p)
{

}

std::vector<double> calculate_expected_chain()
{
  
}
