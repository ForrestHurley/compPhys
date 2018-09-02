#include "random_walk.h"
#include "regression.h"
#include "box_counting.h"
#include "avoiding_random_walk.h"

#include <iostream>
#include <iomanip>
#include <cmath>

#define DIMENSION_COUNT 2
#define WALK_TYPE double

void test_fractal_dim(int iterations, int length, bool verbose)
{
  std::vector<double> frac_dims, frac_sigmas;

  for (int i = 0; i < iterations; i++)
  {
    if (verbose && i % 10 == 0)
      std::cout << std::setprecision(6) << "\rPercent Done: " << (double)i / iterations * 100. << std::flush;
    random_walk_with_memory<DIMENSION_COUNT, WALK_TYPE> walk;
    walk.step_walk(length);

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

int main(){
  //test_fractal_dim(1000, 100000, true);

  avoiding_random_walk<DIMENSION_COUNT, WALK_TYPE> walk;
  walk.verbose = 2;
  walk.step_walk(1000);

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
  std::cout << "Steps: << " << walk.get_total_steps() << std::endl;

  std::cout << "Regression Points:" << std::endl;
  std::vector<double> x, y;
  regress.get_data_points(x, y);
  for(unsigned int i = 0; i < x.size(); i++)
    std::cout << std::setw(4) << std::fixed << std::setprecision(2)
      << "x: " << x[i] << " | y: " << y[i] << std::endl;
  
  walk.write_to_file("outfile.csv");

  /*for (unsigned int i = 0; i < last_loc.size(); i++)
  {
    for (unsigned int j = 0; j < last_loc[0].size(); j++)
      std::cout << last_loc[i][j] << ",";
    std::cout << std::endl;
  }*/

  return 0;
}
