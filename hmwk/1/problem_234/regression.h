#ifndef REGRESSION
#define REGRESSION

#include <vector>

class regression
{
private:
  std::vector<double> x;
  std::vector<double> y;

  //y ~ a + bx
  double b;
  double a;
  
  double r;
  double sigma_b;
  double sigma_a;

  bool calculated;

public:
  regression();

  static double mean(std::vector<double> x);

  static double variance(std::vector<double> x);
  static double variance(std::vector<double> x, double mean_val);

  static double covariance(std::vector<double> x, std::vector<double> y);
  static double covariance(std::vector<double> x, std::vector<double> y,
                    double x_mean, double y_mean);

  double calculate(std::vector<int> x, std::vector<int> y);
  double calculate(std::vector<double> x, std::vector<double> y);

  void get_data_points(std::vector<double>& x, std::vector<double>& y);

  double get_slope();
  double get_intercept();

  double get_slope_sigma();
  double get_intercept_sigma();
};

#endif
