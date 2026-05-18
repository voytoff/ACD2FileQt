#ifndef DATABLOCKARRAY_H
#define DATABLOCKARRAY_H

#include "parameter.h"
#include <QList>
class DataBlock;
class DataBlockArray : public QList<Parameter>
{
public:
  DataBlockArray(QString name, int frequency, int persecond);
  QString name;
  int frequency;
  int persecond;
  void setData(QVector<Parameter*> data);
};

#endif // DATABLOCKARRAY_H
