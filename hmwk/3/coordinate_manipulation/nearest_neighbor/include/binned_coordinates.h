#ifndef BINNED_COORDINATES_H
#define BINNED_COORDINATES_H

#include <vector>
#include "coordinate.h"

class BinnedCoordinates
{
private:
  std::vector<int> bin_counts;

public:
  BinnedCoordinates(std::vector<int> bin_counts);
  BinnedCoordinates(const std::vector<Coordinate*>& locations, const std::vector<double>& bin_dimensions);

  std::vector<int> getBinIndex(Coordinate& location);
  int getBinNumber(Coordinate& location);

  std::vector<int> getBinCounts();
  int getTotalBins();
};

#endif
