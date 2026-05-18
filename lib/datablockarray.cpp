#include "datablockarray.h"

DataBlockArray::DataBlockArray(QString name, int frequency, int persecond)
  : QList<Parameter>()
  , name(name)
  , frequency(frequency)
  , persecond(persecond) {}

void DataBlockArray::setData(QVector<Parameter*> data) {
}
