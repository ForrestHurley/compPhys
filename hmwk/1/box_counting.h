#ifndef BOX_COUNTING
#define BOX_COUNTING

#include "regression.h"
#include "point_hash.h"
#include <vector>
#include <array>
#include <unordered_set>
#include <algorithm>
#include <iostream>

template <int N>
class box_counter
{
public:
  int initial_box;
  double scaling_factor;
  int number_points;

  bool verbose = false;

  box_counter();
  box_counter(int initial_box, double scaling_factor, int number_points);

  double get_fractal_dimension(std::vector<std::array<int, N>> data);
  double get_fractal_dimension(std::vector<std::array<int, N>> data, regression &regression_result);
  double get_fractal_dimension(std::vector<std::array<double, N>> data);
  double get_fractal_dimension(std::vector<std::array<double, N>> data, regression &regression_result);
};

template <int N>
box_counter<N>::box_counter()
{
  initial_box = 1;
  scaling_factor = 2.;
  number_points = 4;
}

template <int N>
box_counter<N>::box_counter(int initial_box, double scaling_factor, int number_points)
{
  this->initial_box = initial_box;
  this->scaling_factor = scaling_factor;
  this->number_points = number_points;
}

template <int N>
double box_counter<N>::get_fractal_dimension(std::vector<std::array<int, N>> data)
{
  std::vector<std::array<double, N>> db_data;
  db_data.reserve(data.size());

  for (std::array<int, N> point : data)
  {
    std::array<double, N> db_point;
    for (unsigned int i = 0; i < point.size(); i++)
      db_point[i] = point[i];
    db_data.push_back(db_point);
  }

  return get_fractal_dimension(db_data);
}

template <int N>
double box_counter<N>::get_fractal_dimension(std::vector<std::array<int, N>> data, regression &regression_result)
{
  std::vector<std::array<double, N>> db_data;
  db_data.reserve(data.size());

  for (std::array<int, N> point : data)
  {
    std::array<double, N> db_point;
    for (unsigned int i = 0; i < point.size(); i++)
      db_point[i] = point[i];
    db_data.push_back(db_point);
  }

  return get_fractal_dimension(db_data, regression_result);
}

template <int N>
double box_counter<N>::get_fractal_dimension(std::vector<std::array<double, N>> data)
{
  regression out;
  return get_fractal_dimension(data, out);
}

template <int N>
double box_counter<N>::get_fractal_dimension(std::vector<std::array<double, N>> data, regression &regression_result)
{
  std::vector<double> sizes, box_sizes;
  sizes.reserve(number_points);
  box_sizes.reserve(number_points);

  double box_size = initial_box;
  for (int i = 0; i < number_points; i++)
  {
    if (verbose)
      std::cout << "\rCalculating filled boxes of size " << box_size << std::flush;

    std::vector<std::array<int, N>> transformed;
    transformed.reserve(data.size());

    for (unsigned int loc = 0; loc < data.size(); loc++)
    {
      std::array<int, N> latticed_element;
      for (int dim = 0; dim < N; dim++)
        latticed_element[dim] = data[loc][dim] / box_size;
      transformed.push_back(latticed_element);
    }


    //TODO: THis is currently the slowest line for large array. It could be swapped for an array of bytes split into bool values for small to medium cases.
    std::unordered_set<std::array<int, N>, int_array_hash<N>> box_set(transformed.begin(), transformed.end());

    sizes.push_back(log(box_set.size()));
    box_sizes.push_back(log(1. / box_size));

    box_size = box_size * scaling_factor;
  }

  if (verbose)
    std::cout << std::endl;

  regression_result.calculate(box_sizes, sizes);

  return regression_result.get_slope();
}

#endif
