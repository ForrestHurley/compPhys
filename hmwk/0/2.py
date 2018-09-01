import numpy as np

#another way to do this would be with a length dimensional numpy array. That might be faster
def vector_generator(length = 4):

  for n in range(2 ** length):

    binary = np.binary_repr(n)

    out = np.array([int(e) for e in binary])
    out = np.pad(out, (length - out.shape[0],0), 'constant', constant_values=0)
    out = out * 2 - 1

    yield out

def e(vector):
  return np.sum(vector * np.roll(vector, 1))

def main():
  e_values = np.array([e(p) for p in vector_generator(4)])
  single_elements = np.exp(-e_values) * e_values
  summed_vals = np.sum(single_elements)
  print("The sum is", summed_vals)

if __name__ == "__main__":
  main()
