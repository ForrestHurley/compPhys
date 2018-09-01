import numpy as np

#the result of this product depends on whether 1 or 0 indexing is used I think
def mult(a, b):
  n = a.shape[0]

  #check that all input matrices have the same dimensions
  assert(
    np.all(
      n == np.array([a.shape, b.shape])))

  c = np.zeros((n,n))

  #TODO: swap for using einsum along with a checkered array
  for i in range(n):
    for j in range(n):
      for k in range(n):
        c[i, j] += (-1) ** (i + j + k) * a[i, k] * b[k, j]

  return c

def main():
  a1 = np.array([[1, 3],
                [2, 4]])
  b1 = np.array([[3, 0],
                [1, 1]])

  a2 = np.array([[3, 2, 1],
                [3, 4, 5],
                [2, 0, 2]])
  b2 = np.array([[5, 3, 4],
                [4, 2, 3],
                [3, 5, 1]])

  a3 = np.ones((4, 4))
  b3 = np.ones((4, 4))

  a4 = np.ones((5, 5))
  b4 = np.ones((5,5))

  c1 = mult(a1, b1)
  c2 = mult(a2, b2)
  c3 = mult(a3, b3)
  c4 = mult(a4, b4)

  print("c1:\n", c1)
  print("c2:\n", c2)
  print("c3:\n", c3)
  print("c4:\n", c4)

if __name__ == "__main__":
  main()
