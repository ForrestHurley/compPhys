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

mpfr::mpreal average_chains::calc_expected_value(std::vector<mpfr::mpreal> values, std::vector<mpfr::mpreal> weights)
{
  //kahan summation algorithm
  mpfr::mpreal sum, y, t, c;
  sum = c = 0.;
  for (unsigned int i = 0; i < values.size(); i++)
  {
    y = values[i] * weights[i] - c;
    t = sum + y;
    c = (t - sum) - y;
    sum = t;
  }

  return sum;
}

void average_chains::add_chain(std::vector<double> y, std::vector<double> p)
{
  y_values.push_back(y);
  probabilities.push_back(p);
}

std::vector<double> average_chains::calculate_expected_chain()
{
  std::vector<double> expected_values;
  std::vector<mpfr::mpreal> accumulated_probabilities;

  for (unsigned int i = 0; i < y_values.size(); i++)
    accumulated_probabilities.push_back(1.);

  std::vector<mpfr::mpreal> single_iter_values(y_values.size());
  bool finished;
  unsigned int idx = 0;
  while (true)
  {
    //update probabilities and check if finished
    finished = true;
    //std::cout << std::endl;
    for (unsigned int i = 0; i < probabilities.size(); i++)
    {
      if (probabilities[i].size() > idx /*&& y_values[i].size() > idx*/)
      {
        accumulated_probabilities[i] *= probabilities[i][idx];
        single_iter_values[i] = y_values[i][idx];
        finished = false;
        //std::cout << probabilities[i][idx] << "|" << accumulated_probabilities[i] << " ";
      }
      else
      {
        accumulated_probabilities[i] = 0;
        //std::cout << ";" << accumulated_probabilities[i] << " ";
      }
    }
    //std::cout << std::endl;

    if (finished)
      break;

    norm_prob(accumulated_probabilities);

    //calculated expected value based on normalized probabilities
    mpfr::mpreal expected_value = calc_expected_value(single_iter_values, accumulated_probabilities);
    expected_values.push_back((double)expected_value);

    idx++;
  }

  return expected_values;
}
