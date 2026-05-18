#ifndef LIB_H
#define LIB_H

#include <QList>

class lib
{
public:
  lib();
  static double round(double value, int digits);
  static double avg(QList<double> array);
};

#endif // LIB_H
