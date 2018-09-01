#ifndef POINT_HASH
#define POINT_HASH

#include <cstdlib>

template <int N>
struct int_array_hash
{
  std::size_t operator()(const std::array<int, N>& a) const
  {
    size_t out = 7927;
    for(int i = 0; i < N; i++)
      out = (out + 2 * abs(a[i]) + (a[i] < 0)) * 8831;
    return out;
  }
};

#endif
