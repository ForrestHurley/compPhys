#include "regression.h"
#include <cassert>
#include <cmath>
#include <iostream>

regression::regression()
{
  calculated = false;
}

//might be worth changing to avoid overflow issues later
double regression::mean(std::vector<double> x)
{
  double sum = 0.;
  for (double num : x)
    sum += num;
  return sum / x.size();
}

double regression::variance(std::vector<double> x)
{
  const double mean_val = mean(x);
  return variance(x, mean_val);
}

double regression::variance(std::vector<double> x, double mean_val)
{
  double sum = 0.;
  for (double num : x)
  {
    const double difference = num - mean_val;
    sum += difference * difference;
  }
  return sum / (x.size() - 1);
}

double regression::covariance(std::vector<double> x, std::vector<double> y)
{
  const double x_mean = mean(x);
  const double y_mean = mean(y);
  return covariance(x, y, x_mean, y_mean);
}

double regression::covariance(std::vector<double> x, std::vector<double> y,
                              double x_mean, double y_mean)
{
  double sum = 0.;

  assert(x.size() == y.size());
  const int size = x.size();

  for (int i = 0; i < size; i++)
  {
    const double x_diff = x[i] - x_mean;
    const double y_diff = y[i] - y_mean;
    sum += x_diff * y_diff;
  }
  return sum / (size - 1);
}

double regression::calculate(std::vector<int> x, std::vector<int> y)
{
  std::vector<double> double_x(x.begin(), x.end());
  std::vector<double> double_y(y.begin(), y.end());
  return calculate(double_x, double_y);
}

double regression::calculate(std::vector<double> x, std::vector<double> y)
{
  assert(x.size() == y.size());
  const int size = x.size();

  const double mean_x = mean(x);
  const double mean_y = mean(y);

  const double var_x = variance(x, mean_x);
  const double var_y = variance(y, mean_y);

  const double cov = covariance(x, y, mean_x, mean_y);

  b = cov / var_x;
  a = mean_y - b * mean_x;

  r = cov / (sqrt(var_x) * sqrt(var_y));

  sigma_b = sqrt( (var_y - b * cov) / (var_x * (size - 2)) );

  std::vector<double> x_sqr = x;
  for (double &num : x_sqr) num *= num;
  sigma_a = sigma_b * sqrt( mean(x_sqr) );

  this->x = x;
  this->y = y;

  calculated = true;

  return r;
}

void regression::get_data_points(std::vector<double>& x, std::vector<double>& y)
{
  assert(calculated);
  x = this->x;
  y = this->y;
}

double regression::get_slope()
{
  assert(calculated);
  return b;
}

double regression::get_intercept()
{
  assert(calculated);
  return a;
}

double regression::get_slope_sigma()
{
  assert(calculated);
  return sigma_b;
}

double regression::get_intercept_sigma()
{
  assert(calculated);
  return sigma_a;
}
