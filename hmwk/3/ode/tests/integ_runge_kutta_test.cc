
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
  integrator.setState(state);
  integrator.EvolveState(10, 10, 0);

  EXPECT_DOUBLE_EQ(state.at(0).at(0), 0.);
  EXPECT_DOUBLE_EQ(state.at(1).at(0), 2.);
}

TEST(RungeKuttaIntegratorTest, LinearIntegrationTest)
{
  PolynomialFunction foo = PolynomialFunction(std::vector<double>{1., 2.});
  RungeKuttaIntegrator integrator = RungeKuttaIntegrator(&foo);

  std::vector< std::vector<double> > state = 
    std::vector< std::vector<double> >{ std::vector<double>{0.}, std::vector<double>{2.}};
  integrator.setState(state);
  integrator.EvolveState(10, 10, 0);

  EXPECT_DOUBLE_EQ(state.at(0).at(0), 110.);
  EXPECT_DOUBLE_EQ(state.at(1).at(0), 112.);
}

TEST(RungeKuttaIntegratorTest, QuadraticIntegrationTest)
{
  PolynomialFunction foo = PolynomialFunction(std::vector<double>{1., -2., 3.});
  RungeKuttaIntegrator integrator = RungeKuttaIntegrator(&foo);

  std::vector< std::vector<double> > state = 
    std::vector< std::vector<double> >{ std::vector<double>{0.}, std::vector<double>{2.}};
  integrator.setState(state);
  integrator.EvolveState(10, 10, 0);

  EXPECT_DOUBLE_EQ(state.at(0).at(0), 910.);
  EXPECT_DOUBLE_EQ(state.at(1).at(0), 912.);
}

TEST(RungeKuttaIntegratorTest, TwoLevelIntegrationTest)
{
  PolynomialFunction foo = PolynomialFunction(std::vector<double>{0.});
  RungeKuttaIntegrator integrator = RungeKuttaIntegrator(&foo);

  std::vector< std::vector<double> > state = 
    std::vector< std::vector<double> >{ std::vector<double>{0., 0.}};
  integrator.setState(state);
  integrator.EvolveState(10, 10, 0);

  EXPECT_DOUBLE_EQ(state.at(0).at(0), 0.);
  EXPECT_DOUBLE_EQ(state.at(0).at(1), 0.);

  PolynomialFunction foo2 = PolynomialFunction(std::vector<double>{1.});
  RungeKuttaIntegrator integrator2 = RungeKuttaIntegrator(&foo2);

  std::vector< std::vector<double> > state2 = 
    std::vector< std::vector<double> >{ std::vector<double>{0., 0.}};
  integrator2.setState(state2);
  integrator2.EvolveState(10, 10, 0);

  EXPECT_DOUBLE_EQ(state2.at(0).at(0), 50.);
  EXPECT_DOUBLE_EQ(state2.at(0).at(1), 10.);
}

TEST(RungeKuttaIntegratorTest, TwoLevelVectorizedTest)
{
  PolynomialFunction foo = PolynomialFunction(std::vector<double>{2., 6.});
  RungeKuttaIntegrator integrator = RungeKuttaIntegrator(&foo);

  std::vector< std::vector<double> > state = 
    std::vector< std::vector<double> >{ std::vector<double>{0., 0.}, std::vector<double> {1., -1.}};
  integrator.setState(state);
  integrator.EvolveState(10, 10, 0);

  EXPECT_DOUBLE_EQ(state.at(0).at(0), 1100.);
  EXPECT_DOUBLE_EQ(state.at(0).at(1), 320.);
  EXPECT_DOUBLE_EQ(state.at(1).at(0), 1091.);
  EXPECT_DOUBLE_EQ(state.at(1).at(1), 319.);
}

class FlattenedFunction : public ODEInterface
{
  double a, b;
public:
  FlattenedFunction(double a, double b) :
    ODEInterface(2), a(a), b(b) {}

  std::vector<double> CalculateHighestDerivative(
    const std::vector< std::vector<double> > &values, double time)
  {
    int size = values.size() / 2;
    assert(size * 2 == values.size());
    std::vector<double> out;
    for (int i = 0; i < size; i++)
    {
      assert(values.at(i + size).size() == 1);
      out.push_back(a * values.at(i + size).at(0));
    }
    for (int i = 0; i < size; i++)
    {
      assert(values.at(i).size() == 1);
      out.push_back(b * values.at(i).at(0));
    }
    return out;
  }
};

TEST(RungeKuttaIntegratorTest, FlattenedIntegrationTest)
{
  FlattenedFunction foo = FlattenedFunction(0., 0.);
  RungeKuttaIntegrator integrator = RungeKuttaIntegrator(&foo, true);

  std::vector< std::vector<double> > state =
    std::vector< std::vector<double> >{ std::vector<double>{0., 0.}, std::vector<double>{2., -2.}};
  integrator.setState(state);
  integrator.EvolveState(10, 10, 0);

  EXPECT_DOUBLE_EQ(state.at(0).at(0), 0.);
  EXPECT_DOUBLE_EQ(state.at(0).at(1), 0.);
  EXPECT_DOUBLE_EQ(state.at(1).at(0), 2.);
  EXPECT_DOUBLE_EQ(state.at(1).at(1), -2.);

  FlattenedFunction foo2 = FlattenedFunction(1., -1.);
  RungeKuttaIntegrator integrator2 = RungeKuttaIntegrator(&foo2, true);

  std::vector< std::vector<double> > state2 =
    std::vector< std::vector<double> >{ std::vector<double>{0., 0.}, std::vector<double>{-1., 1.}};
  integrator2.setState(state2);
  integrator2.EvolveState(3.1415927, 100, 0);

  EXPECT_DOUBLE_EQ(state2.at(0).at(0), 0.);
  EXPECT_DOUBLE_EQ(state2.at(0).at(1), 0.);
  EXPECT_NEAR(state2.at(1).at(0), 1., 0.001);
  EXPECT_NEAR(state2.at(1).at(1), -1., 0.001);
}
