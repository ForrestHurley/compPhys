#ifndef EXPECTED_CHAIN_VALUE
#define EXPECTED_CHAIN_VALUE

#include <vector>
#include <mpreal.h>

class average_chains
{
private:
  std::vector<std::vector<double>> y_values;
  std::vector<std::vector<double>> probabilities;

  int bits_of_precision = 128;

  void norm_prob(std::vector<mpfr::mpreal>& in_probs);
  mpfr::mpreal calc_expected_value(std::vector<mpfr::mpreal> values, std::vector<mpfr::mpreal> weights);
  mpfr::mpreal calc_expected_value_uniform(std::vector<mpfr::mpreal> values);

public:
  void add_chain(std::vector<double> y, std::vector<double> p);

  std::vector<double> calculate_expected_chain();
  std::vector<double> calculate_expected_chain(bool assume_uniform);

  void set_precision();
  int get_precision();

  bool verbose = false;
};

#endif
