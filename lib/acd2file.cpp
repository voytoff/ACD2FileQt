#include "acd2file.h"

ACD2File::ACD2File() {}

double ACD2File::round(double value, int digits) {
  double factor = std::pow(10, digits);
  return std::round(value * factor) / factor;
}
