#ifndef METRIC_SPACE_H
#define METRIC_SPACE_H

#include <vector>

class MetricSpace
{
public:
  class MetricPoint
  {
  private:
    const MetricSpace* space;

  public:
    MetricPoint(MetricSpace* space) : space(space) {}

    virtual ~MetricPoint() = default;

    const MetricSpace* getSpace() const { return space; } 
  };

private:
  std::vector<MetricPoint*> point_list;

public:
  virtual ~MetricSpace()
  {
    for (MetricPoint* point : point_list) delete point;
  }

  virtual double Distance(const MetricPoint& A, const MetricPoint& B) const = 0;

  virtual const MetricPoint& getOrigin() const = 0;
  virtual void addPoint(MetricPoint* point) { point_list.push_back(point); }
};

#endif
