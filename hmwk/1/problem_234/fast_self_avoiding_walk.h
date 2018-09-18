#ifndef FAST_SELF_AVOIDING_WALK
#define FAST_SELF_AVOIDING_WALK

#include "avoiding_lattice_walk.h"
#include <math.h>

template <int N>
class avoiding_distributed_lattice_walk : public avoiding_lattice_walk<N>
{
  std::vector<double> probabilities;
  double last_probability;

protected:
  std::array<int, N> generate_random_step() override;
  bool step_forwards(int steps) override;

  void pop_point() override;

  virtual std::array<int, N * 2> find_direction_counts(int depth = 0) = 0;
public:
  std::vector<double> get_probabilities() override;
};

template <int N>
class avoiding_counting_lattice_walk : public avoiding_distributed_lattice_walk<N>
{
private:
  int maximum_depth = 4;

protected:
  std::array<int, N * 2> find_direction_counts(int depth = 0) override;
};

template <int N>
class avoiding_random_lattice_walk : public avoiding_distributed_lattice_walk<N>
{
private:
  int exponential_steps = 2;
  int branching_factor = 10;
  int maximum_depth = 200;

  bool single_test_step(std::vector<std::array<int, N>>& step_list);
  bool single_test_step(std::vector<std::array<int, N>>& step_list, int& n);
  int generate_test_avoiding_walk(int& initial_direction);

protected:
  std::array<int, N * 2> find_direction_counts(int depth = 0) override;
};

template <int N>
std::array<int, N> avoiding_distributed_lattice_walk<N>::generate_random_step()
{
  std::array<int, N * 2> direction_counts = find_direction_counts();

  //std::cout << "Found counts" << std::endl;

  static thread_local std::mt19937_64 engine(time(0));
  std::discrete_distribution<int> distribution (direction_counts.begin(), direction_counts.end());

  //std::cout << "Created dist" << std::endl;

  int n = distribution(engine);
  last_probability = distribution.probabilities()[n];

  //std::cout << "Random n" << std::endl;

  return this->generate_nth_step(n);
}

template <int N>
bool avoiding_distributed_lattice_walk<N>::step_forwards(int steps)
{
  for (int i = 0; i < steps; i++)
  {
    if (!avoiding_lattice_walk<N>::step_forwards(1))
      return false;

    probabilities.push_back(last_probability);
  }
  return true;
}

template <int N>
void avoiding_distributed_lattice_walk<N>::pop_point()
{
  probabilities.pop_back();
  avoiding_lattice_walk<N>::pop_point();
}

template <int N>
std::vector<double> avoiding_distributed_lattice_walk<N>::get_probabilities()
{
  return probabilities;
}

template <int N>
std::array<int, N * 2> avoiding_counting_lattice_walk<N>::find_direction_counts(int depth)
{
  std::array<int, N * 2> out;
  for (int i = 0; i < N * 2; i++)
    out[i] = 0;

  if (depth < maximum_depth)
  {
    auto step_list = this->generate_all_steps();

    for (int idx = 0; idx < N * 2; idx ++)
    {
      if (this->take_step(step_list[idx]))
      {
        std::array<int, N * 2> temp_counts = find_direction_counts(depth + 1);
        out[idx] = std::accumulate(temp_counts.begin(), temp_counts.end(), 0) + 1;
        avoiding_lattice_walk<N>::pop_point();
      }
    }
  }
  else
  {
    out[0] = 1;
  }

  return out;
}

template <int N>
std::array<int, N * 2> avoiding_random_lattice_walk<N>::find_direction_counts(int depth)
{
  std::array<int, N * 2> out;
  for (int i = 0; i < N * 2; i++)
    out[i] = 0;

  std::array<int, N> last_step = this->get_last_step();

  if (depth < exponential_steps)
  {
    //std::cout << "Exponential step" << std::endl;
    auto step_list = this->generate_all_steps();

    for (int idx = 0; idx < N * 2; idx++)
    {
      if (this->take_step(step_list[idx]))
      {
        //std::cout << "N: " << idx << " Length: " << this->get_length() << std::endl;
        std::array<int, N * 2> temp_counts = find_direction_counts(depth + 1);
        out[idx] = std::accumulate(temp_counts.begin(), temp_counts.end(), 0) + 1;
        avoiding_lattice_walk<N>::pop_point();
      }
    }
  }
  else
  {
    int initial_step_index;
    int count;
    //std::cout << "Random step" << std::endl;

    int starting_size = this->get_length();

    for (int idx = 0; idx < branching_factor; idx++)
    {
      count = generate_test_avoiding_walk(initial_step_index);
      out[initial_step_index] += count;

      this->set_last_step(last_step);
      int removal_count = this->get_length() - starting_size;
      for (int i = 0; i < removal_count; i++)
        avoiding_lattice_walk<N>::pop_point();
    }
  }

  /*std::cout << "Finished step ";
  for (int i = 0; i < N * 2; i++)
    std::cout << out[i] << " ";
  std::cout << std::endl;*/

  return out;
}

template <int N>
bool avoiding_random_lattice_walk<N>::single_test_step(std::vector<std::array<int, N>>& step_list)
{
  int n = 0;
  return single_test_step(step_list, n);
}
template <int N>
bool avoiding_random_lattice_walk<N>::single_test_step(std::vector<std::array<int, N>>& step_list, int& n)
{

  static thread_local std::mt19937_64 engine(time(0));
  static thread_local std::uniform_int_distribution<int> distribution(0, N * 2 - 1);

  std::array<int, N> random_step;

  int repeats = 0;
  do
  {
    n = distribution(engine);
    random_step = step_list[n]; 

    if (repeats == 10)
    {
      return false;
    }
    repeats++;
  } while (this->same_as_last_step(random_step));

  this->set_last_step(random_step);

  if (!this->take_step(random_step))
    return false;
  return true;
}

template <int N>
int avoiding_random_lattice_walk<N>::generate_test_avoiding_walk(int& initial_direction)
{
  auto step_list = this->generate_all_steps();

  if (!single_test_step(step_list, initial_direction))
    return 0;

  int i;
  for (i = 1; i < maximum_depth - exponential_steps; i++)
  {
    if (!single_test_step(step_list))
      break;
  }
  return i;
}

#endif
