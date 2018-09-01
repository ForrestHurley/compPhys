import numpy as np
from scipy.spatial.distance import pdist, squareform
from itertools import permutations
import matplotlib.pyplot as plt

def generate_points(num = 7):
  return np.random.rand(num, 2) #technically this is [0,1) rather than (0,1)

def calculate_distance_matrix(point_array):
  return squareform(#Not strictly necessary to convert and is less efficient, but easier to program
    pdist(point_array, 'euclidean'))

def generate_paths(num = 7):
  return permutations(list(range(num)))

def generate_path_lengths(distance_matrix):
  n = distance_matrix.shape[0]

  for path in generate_paths(n):
    distances = [distance_matrix[a,b]
      for a, b in zip(path, path[1:])]

    yield sum(distances), path

def main():
  points = generate_points(num = 7)
  dist_matr = calculate_distance_matrix(points)

  length, shortest_path = min(generate_path_lengths(dist_matr))

  print("Points:\n", points)
  print("Shortest path:\n", shortest_path)
  print("Path length:\n", length)

  ordered_points = points[list(shortest_path)]
  plt.plot(ordered_points[:, 0], ordered_points[:, 1], c = 'r')
  plt.scatter(points[:, 0], points[:, 1])
  plt.show()

if __name__ == "__main__":
  main()
