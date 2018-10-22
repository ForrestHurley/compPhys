
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "integ_runge_kutta.h"

TEST(RungeKuttaIntegratorTest, ConstructionTest)
{

}

class PolynomialFunction : public ODEInterface
{
  std::vector<double> values;
public:
  PolynomialFunction(std::vector<double> values) :
    ODEInterface(), values(values) {}

  std::vector<double> CalculateHighestDerivative(
    const std::vector< std::vector<double> > &values, double time)
  {
    double out = 0.;
    for (int j = this->values.size() - 1; j > -1; j--)
      out = out * time + this->values.at(j);
    return std::vector<double>(values.size(), out);
  }
};

TEST(RungeKuttaIntegratorTest, ZeroIntegrationTest)
{
  PolynomialFunction foo = PolynomialFunction(std::vector<double>{});
  RungeKuttaIntegrator integrator = RungeKuttaIntegrator(&foo);

  std::vector< std::vector<double> > state = 
    std::vector< std::vector<double> >{ std::vector<double>{0.}, std::vector<double>{2.}};
  integrator.EvolveState(state, 10, 10, 0);

  ASSERT_DOUBLE_EQ(state.at(0).at(0), 0.);
  ASSERT_DOUBLE_EQ(state.at(1).at(0), 2.);
}

TEST(RungeKuttaIntegratorTest, LinearIntegrationTest)
{
  PolynomialFunction foo = PolynomialFunction(std::vector<double>{1., 2.});
  RungeKuttaIntegrator integrator = RungeKuttaIntegrator(&foo);

  std::vector< std::vector<double> > state = 
    std::vector< std::vector<double> >{ std::vector<double>{0.}, std::vector<double>{2.}};
  integrator.EvolveState(state, 10, 10, 0);

  ASSERT_DOUBLE_EQ(state.at(0).at(0), 110.);
  ASSERT_DOUBLE_EQ(state.at(1).at(0), 112.);
}

TEST(RungeKuttaIntegratorTest, QuadraticIntegrationTest)
{
  PolynomialFunction foo = PolynomialFunction(std::vector<double>{1., -2., 3.});
  RungeKuttaIntegrator integrator = RungeKuttaIntegrator(&foo);

  std::vector< std::vector<double> > state = 
    std::vector< std::vector<double> >{ std::vector<double>{0.}, std::vector<double>{2.}};
  integrator.EvolveState(state, 10, 10, 0);

  ASSERT_DOUBLE_EQ(state.at(0).at(0), 910.);
  ASSERT_DOUBLE_EQ(state.at(1).at(0), 912.);
}

TEST(RungeKuttaIntegratorTest, TwoLevelIntegrationTest)
{
  PolynomialFunction foo = PolynomialFunction(std::vector<double>{1.});
  RungeKuttaIntegrator integrator = RungeKuttaIntegrator(&foo);

  std::vector< std::vector<double> > state = 
    std::vector< std::vector<double> >{ std::vector<double>{0., 0.}, std::vector<double>{2., 1.}};
  integrator.EvolveState(state, 10, 10, 0);

  ASSERT_DOUBLE_EQ(state.at(0).at(0), 910.);
  ASSERT_DOUBLE_EQ(state.at(1).at(0), 912.);
}
