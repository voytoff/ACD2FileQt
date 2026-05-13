#include "parameter.h"

Parameter::Parameter() {}

Parameter::Parameter(double index, QDateTime time, double value) {
  this->index = index;
  this->time = time;
  this->value = value;
}
