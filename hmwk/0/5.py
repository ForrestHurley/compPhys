import random
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from mpl_toolkits.mplot3d import Axes3D
import collections
from operator import mul
from functools import reduce

class lattice:
  def __init__(self, data = None, n = (10, 10)):

    self._value_grid = None
    self._graph_repr = None
    self._connected_components = None

    if data is None:
      self._generate_lattice(n = n)
      self._shape = n
    elif not isinstance(data, (collections.Sequence, np.ndarray)):
      self._generate_lattice(n = n)
      self._shape = n
      self._fill_lattice(initial_value = data)
    else:
      data = np.array(data)
      self._shape = data.shape
      self._lattice_from_values(data)

  @property
  def lattice_positions(self):
    product = reduce(mul, self.shape)

    for i in range(product):
      yield self.get_node_indices(np.array([i]))[0]

  @property
  def edge_list(self):

    edges = []

    for i, node_index in enumerate(self.lattice_positions): #TODO: add vectorized version for reasonably sized graphs

      node_tuple = tuple(node_index)
      for j in range(len(self.shape)):

        other_index = node_index.copy()
        other_index[j] += 1

        if other_index[j] < self.shape[j]:
          if self.node_values[node_tuple] == \
            self.node_values[tuple(other_index)]:
            edges.append((i, self.get_node_numbers(np.array([other_index]))[0]))

    return edges

  @property
  def shape(self):
    return self._shape

  @property
  def as_graph(self):
    if self._graph_repr is None:
      self._graph_repr = nx.Graph()
      self._graph_repr.add_edges_from(self.edge_list)
    return self._graph_repr

  @property
  def connected_components(self):
    if self._connected_components is None:
      self._connected_components = nx.connected_components(self.as_graph)
    return self._connected_components

  @property
  def node_values(self):
    return self._value_grid

  def _generate_lattice(self, n = (10, 10)):
    self._value_grid = np.zeros(n)

  def _fill_lattice(self, initial_value = 0):
    self._value_grid.fill(initial_value)

  def _lattice_from_values(self, data):
    self._value_grid = data

  def get_node_numbers(self, index_array):
    size_counts = np.cumprod((1,) + self.shape)[:-1]

    out_nums = np.zeros(index_array.shape[0], dtype = int)

    for i, elem_size in enumerate(size_counts):
      out_nums += index_array[:, i] * elem_size

    return out_nums

  def get_node_indices(self, number_array):
    size_counts = np.cumprod((1,) + self.shape)[:-1]

    out_indices = np.zeros((number_array.shape[0], len(self.shape)), dtype = int)

    for i, elem_size in reversed(list(enumerate(size_counts))):
      divided = ( number_array // elem_size ).astype(dtype=int) 
      out_indices[:,i] = divided
      number_array -= divided * elem_size

    return out_indices

  def check_connected_point_sets(self, a, b):

    components = self.connected_components

    a_set = set(self.get_node_numbers(a))
    b_set = set(self.get_node_numbers(b))

    for component in components:
      temp_node_set = set(component)

      if (not temp_node_set.isdisjoint(a_set)) and \
        (not temp_node_set.isdisjoint(b_set)):
        return True

    return False
    
  def graph_lattice(self, show = False, *args):
    
    colors = self.node_values.flatten()

    lattice_positions = np.array(list(self.lattice_positions))
    dimensions = len(self.shape)
    fig = plt.figure()

    if dimensions == 1:
      plt.scatter(lattice_positions[:, 0],
        np.broadcast(0, lattice_positions.shape[0]),
        c = colors)
    if dimensions == 2:
      plt.scatter(lattice_positions[:, 0],
        lattice_positions[:, 1],
        c = colors,
        linewidth = 1.5,
        edgecolor='black',
        cmap = 'Greys')
    if dimensions == 3:
      ax3 = fig.add_subplot(111, projection='3d')
      ax3.scatter(
        xs = lattice_positions[:, 0],
        ys = lattice_positions[:, 1],
        zs = lattice_positions[:, 2],
        c = colors)

    if show:
      plt.show()

#assumes a 2d square lattice
def check_for_path_across(lattice_in, n):
  start_indices = np.array([[x, 0] for x in range(n) if lattice_in.node_values[x, 0] == 1])
  end_indices = np.array([[x, n -1] for x in range(n) if lattice_in.node_values[x, n - 1] == 1])

  if start_indices.shape[0] == 0 or end_indices.shape[0] == 0:
    return False

  return lattice_in.check_connected_point_sets(
    start_indices, end_indices)


def main():

  p = 0.333
  n = 10

  lattice_data = \
    np.where(np.random.rand(n,n) > p, 0, 1)

  percolate_lattice = lattice(data = lattice_data)

  percolate_lattice.graph_lattice(show = True)

  if check_for_path_across(percolate_lattice, n):
    print("Found path")
  else:
    print("Did not find path")

  '''
  path_prob_list = []

  num_steps = 50
  num_repeats = 200
  for i in range(1, num_steps + 1):

    p = i / num_steps
    print("\rCalculate for p =", p, end = "\033[K", flush = True)
    count = 0

    for j in range(num_repeats):

      lattice_data = \
        np.where(np.random.rand(n,n) > p, 0, 1)

      percolate_lattice = lattice(data = lattice_data)

      if check_for_path_across(percolate_lattice, n):
        count += 1

    path_prob_list.append((p, count / num_repeats))

  path_prob_array = np.array(path_prob_list)
  plt.plot(path_prob_array[:, 0], path_prob_array[:, 1])
  plt.show()

  print("")
  '''
if __name__ == "__main__":
  main()
