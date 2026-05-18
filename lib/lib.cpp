#include "lib.h"

lib::lib() {}

double lib::round(double value, int digits) {
  double factor = std::pow(10, digits);
  return std::round(value * factor) / factor;
}

double lib::avg(QList<double> array) {
  double sum = std::accumulate(array.begin(), array.end(), 0.0);
  return sum / array.size();
}
