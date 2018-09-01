import numpy as np
from matplotlib import pyplot as plt
from abc import ABC, abstractmethod

class integrator(ABC):
  def __init__(self,
              minimum = 0,
              maximum = 1,
              steps = 10):
    self.minimum = minimum
    self.maximum = maximum
    self.steps = steps
    self._values = None
    self._foo = lambda x: x

  @property
  def values(self):
    if self._values == None:
      self._values = self._calc_integrate(self._foo)
    return self._values

  @property
  def foo(self):
    return self._foo

  @foo.setter
  def foo(self, value):
    if value != None and callable(value):
      self._foo = value

  @abstractmethod
  def _calc_integrate(self, foo):
    pass

class trapezoidal_integrator(integrator):
  def _calc_integrate(self, foo):
    x = np.linspace(self.minimum,
      self.maximum,
      num = self.steps + 1)

    y = np.nan_to_num(foo(x))

    y_sum = np.cumsum(y)
    y_sum[1:] -= 0.5 * y[0]
    y_sum[1:] -= 0.5 * y[1:]

    y_sum *= (self.maximum - self.minimum) / (self.steps + 1)

    return x, y_sum

def main():
  
  def foo(x):
    return np.sin(x) / np.sqrt(x)

  integ = trapezoidal_integrator(0, 18, 100)
  integ.foo = foo

  plt.plot(*integ.values)
  plt.show()

if __name__ == "__main__":
  main()
