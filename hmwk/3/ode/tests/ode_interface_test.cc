
#include "ode_interface_test.h"

using ::testing::An;
using ::testing::DoubleEq;
using ::testing::Return;
using ::testing::ByRef;
using ::testing::Ref;
using ::testing::_;
using ::testing::Const;
using ::testing::ElementsAre;

TEST(ODEInterfaceTest, ConstructionTest)
{
  MockODEInterface ode_interface_2(2);
  EXPECT_EQ(ode_interface_2.degree, 2);

  MockODEInterface ode_interface_3(3);
  EXPECT_EQ(ode_interface_3.degree, 3);

  MockODEInterface ode_interface_5(5);
  EXPECT_EQ(ode_interface_5.degree, 5);
}

TEST(ODEInterfaceTest, VectorizeTestSingle)
{
  MockODEInterface ode_interface(3);

  EXPECT_CALL(ode_interface, CalculateHighestDerivative(ElementsAre(_, _, _), DoubleEq(1.)) )
    .Times(1).WillOnce(Return(10.));

  std::vector< std::vector<double> > in_vals(1, std::vector<double>(3, 15.));
  EXPECT_EQ(std::vector<double>(1, 10.), ode_interface.CalculateHighestDerivative(in_vals, 1.));
}

TEST(ODEInterfaceTest, VectorizeTestMultiple)
{
  MockODEInterface ode_interface(3);

  EXPECT_CALL(ode_interface, CalculateHighestDerivative(ElementsAre(_, _, _), DoubleEq(1.)) )
    .Times(4)
    .WillOnce(Return(10.))
    .WillOnce(Return(20.))
    .WillOnce(Return(30.))
    .WillOnce(Return(40.));

  std::vector< std::vector<double> > in_vals(4, std::vector<double>(3, 10.));
  std::vector<double> out_vals{10., 20., 30., 40.};

  std::vector<double> return_val = ode_interface.CalculateHighestDerivative(in_vals, 1.);
  EXPECT_EQ(out_vals, return_val);
}

TEST(ODEInterfaceTest, FailOnWrongSizeInput)
{
  //TODO: something different should happen if the last dimension of any of the vectors
  //      in the vector of vectors doesn't match the degree of the ode_interface
  FAIL();
}
