#include "random_walk.h"
#include "lattice_walk.h"
#include "avoiding_lattice_walk.h"
#include "fast_self_avoiding_walk.h"
#include "regression.h"
#include "box_counting.h"
#include "expected_chain_value.h"

#include <iostream>
#include <iomanip>
#include <cmath>

#define DIMENSION_COUNT 2
#define WALK_TYPE int

void test_fractal_dim(int iterations, int length, bool verbose)
{
  std::vector<double> frac_dims, frac_sigmas;

  for (int i = 0; i < iterations; i++)
  {
    if (verbose && i % 10 == 0)
      std::cout << std::setprecision(6) << "\rPercent Done: " << (double)i / iterations * 100. << std::flush;
    lattice_walk<DIMENSION_COUNT> walk;
    walk.make_walk(length);

    std::vector<std::array<WALK_TYPE, DIMENSION_COUNT>> last_loc = walk.get_location_list();

    regression regress;

    box_counter<DIMENSION_COUNT> counter(2, 1.5, 10);
    frac_dims.push_back(counter.get_fractal_dimension(last_loc, regress));
    frac_sigmas.push_back(regress.get_slope_sigma());
  }
  if (verbose)
    std::cout << std::endl;

  double mean = regression::mean(frac_dims);

  std::vector<double> frac_vars = frac_sigmas;
  for (double &val : frac_vars) val *= val;
  double sigma = sqrt(regression::mean(frac_vars)) / sqrt(frac_vars.size());

  std::cout << "Fractal Dimension: " << mean << std::endl;
  std::cout << "Standard Deviation of the mean: " << sigma << std::endl;
}

void weighted_flory_exponent_calc(unsigned long iterations, bool verbose = true, int max_length = 100)
{
  average_chains expected_calc;

  for (unsigned int idx = 0; idx < iterations; idx++)
  {
    if (verbose && idx % 1 == 0)
      std::cout << std::setprecision(6) << "\rPercent Done: " << (double)idx / iterations * 100. << std::flush;

    avoiding_counting_lattice_walk<DIMENSION_COUNT> walk;
    walk.make_walk(max_length, true);

    std::vector<std::array<WALK_TYPE, DIMENSION_COUNT>> point_list = walk.get_location_list();
    std::vector<double> tmp_prob_list = walk.get_probabilities();

    std::vector<double> dist_sqr_list(point_list.size());

    for (unsigned int i = 0; i < point_list.size(); i++)
    {
      double r = 0;
      for (int j = 0; j < DIMENSION_COUNT; j++)
        r += point_list[i][j] * point_list[i][j];
        
      dist_sqr_list[i] = r;
    }

    for (unsigned int i = 0; i < tmp_prob_list.size(); i++)
    {
      tmp_prob_list[i] = 1. / tmp_prob_list[i];
    }

    //std::cout << std::endl << point_list.size() << tmp_prob_list.size() << std::endl;
    expected_calc.add_chain(dist_sqr_list, tmp_prob_list);
  }

  if (verbose)
    std::cout << std::endl << "Calculating expected values" << std::endl;

  std::vector<double> expected_distance_sqr = expected_calc.calculate_expected_chain();
  //std::cout << expected_distance_sqr[2] << std::endl;

  if (verbose)
    std::cout << std::endl;

  int start_cut = 5;
  int end_cut = 10;

  if (expected_distance_sqr.size() - start_cut - end_cut < 5)
  {
    std::cout << "Not enough points" << std::endl;
    start_cut = 0;
    end_cut = 0;
  }

  std::vector<double> x(expected_distance_sqr.size() - start_cut - end_cut - 1);
  std::vector<double> y(expected_distance_sqr.size() - start_cut - end_cut - 1);
    
  for (unsigned int i = 1 + start_cut; i < expected_distance_sqr.size() - end_cut; i++)
  {
    y[i - start_cut - 1] = log(expected_distance_sqr[i]);
    x[i - start_cut - 1] = log(i);
    if (verbose)
      std::cout << i << "," << expected_distance_sqr[i] << std::endl;
  }

  if (verbose)
    std::cout << std::endl << "Number of points to fit: " << y.size() << std::endl;

  regression regress;

  regress.calculate(x, y);

  double flory_exp = regress.get_slope() / 2;
  double flory_sigma = regress.get_slope_sigma() / sqrt(2);

  std::cout << "Flory exponent: " << flory_exp << std::endl;
  std::cout << "Flory exponent sigma: " << flory_sigma << std::endl;
}

void flory_exponent_calc(unsigned long long iterations, bool verbose = true, int max_length = 200)
{
  std::vector<double> r_sqr_list;
  std::vector<int> r_sqr_counts;

  for (unsigned int idx = 0; idx < iterations; idx++)
  {
    if (verbose && idx % 100000 == 0)
      std::cout << std::setprecision(6) << "\rPercent Done: " << (double)idx / iterations * 100. << std::flush;

    avoiding_lattice_walk<DIMENSION_COUNT> walk;
    walk.make_walk(max_length, false);

    std::vector<std::array<WALK_TYPE, DIMENSION_COUNT>> point_list = walk.get_location_list();

    const int size_diff = point_list.size() - r_sqr_list.size();

    for (int i = 0; i < size_diff; i++)
    {
      r_sqr_list.push_back(0.);
      r_sqr_counts.push_back(0);
    }

    for (unsigned int i = 0; i < point_list.size(); i++)
    {
      double r = 0;
      
      for (int j = 0; j < DIMENSION_COUNT; j++)
        r += point_list[i][j] * point_list[i][j];
        
      r_sqr_list[i] += r;
      r_sqr_counts[i]++;
    }
  }

  int start_cut = 5;
  int end_cut = 10;

  if (r_sqr_list.size() - start_cut - end_cut < 5)
  {
    std::cout << "Not enough points" << std::endl;
    start_cut = 0;
    end_cut = 0;
  }

  std::vector<double> x(r_sqr_list.size() - start_cut - end_cut - 1);
  std::vector<double> y(r_sqr_list.size() - start_cut - end_cut - 1);

  if (verbose)
    std::cout << std::endl;
    
  for (unsigned int i = 1 + start_cut; i < r_sqr_list.size() - end_cut; i++)
  {
    y[i - start_cut - 1] = log(r_sqr_list[i] / r_sqr_counts[i]);
    x[i - start_cut - 1] = log(i);
    if (verbose)
      std::cout << x[i - start_cut - 1] << "," << y[i - start_cut - 1] << std::endl;
  }

  if (verbose)
    std::cout << std::endl << "Number of points to fit: " << y.size() << std::endl;

  regression regress;

  regress.calculate(x, y);

  double flory_exp = regress.get_slope() / 2;
  double flory_sigma = regress.get_slope_sigma() / sqrt(2);

  std::cout << "Flory exponent: " << flory_exp << std::endl;
  std::cout << "Flory exponent sigma: " << flory_sigma << std::endl;
}

int main(){
  //test_fractal_dim(1000, 100000, true);

  //weighted_flory_exponent_calc(1000);
  flory_exponent_calc(1000000000);

  /*avoiding_counting_lattice_walk<DIMENSION_COUNT> walk;
  walk.verbose = 2;
  walk.make_walk(1000, false);

  std::vector<std::array<WALK_TYPE, DIMENSION_COUNT>> last_loc = walk.get_location_list();

  regression regress;

  box_counter<DIMENSION_COUNT> counter(2, 1.5, 10);
  counter.verbose = true;
  const double frac_dim = counter.get_fractal_dimension(last_loc, regress);
  
  std::cout << "Last value: ";
  const std::array<WALK_TYPE, DIMENSION_COUNT> last = walk.get_last_location();
  for (WALK_TYPE loc : last) std::cout << loc << ", ";
  std::cout << std::endl;

  std::cout << std::setprecision(4) << "Dimension: " << frac_dim << std::endl;
  std::cout << "Dimension Sigma: " << regress.get_slope_sigma() << std::endl;

  std::cout << "Number of locations: " << last_loc.size() << std::endl;

  std::cout << "Regression Points:" << std::endl;
  std::vector<double> x, y;
  regress.get_data_points(x, y);
  for(unsigned int i = 0; i < x.size(); i++)
    std::cout << std::setw(4) << std::fixed << std::setprecision(2)
      << "x: " << x[i] << " | y: " << y[i] << std::endl;
  
  walk.write_to_file("outfile.csv");*/

  /*for (unsigned int i = 0; i < last_loc.size(); i++)
  {
    for (unsigned int j = 0; j < last_loc[0].size(); j++)
      std::cout << last_loc[i][j] << ",";
    std::cout << std::endl;
  }*/

  return 0;
}
