#ifndef METRIC_SPACE_H
#define METRIC_SPACE_H

class MetricSpace
{
public:
  class MetricPoint {};

  virtual double Distance(const MetricPoint& A, const MetricPoint& B) const = 0;

  virtual const MetricPoint& getOrigin() const = 0;
};

#endif
