#include "channelblock.h"
#include "datablock.h"
#include "parameter.h"
#include "acd2file.h"
#include "lib.h"

ChannelBlock::ChannelBlock(QObject *parent)
  : dataBlockArray(new QList<DataBlock*>())
  , finalData() {
  //dataBlockArray = new QList<DataBlock*>();
}

QDateTime ChannelBlock::start() {
  return (dataBlockArray->count() == 0) ?
           QDateTime() :
           (*std::min_element(dataBlockArray->begin(), dataBlockArray->end(), [](const DataBlock *a, const DataBlock *b) {
             return a->time < b->time;
            }))->time;
}

QDateTime ChannelBlock::stop() {
  return (dataBlockArray->count() == 0) ?
           QDateTime() : // ??
           (*std::max_element(dataBlockArray->begin(), dataBlockArray->end(), [](const DataBlock* a, const DataBlock* b) {
             return a->time < b->time;
            }))->time;
}

void ChannelBlock::add(DataBlock* data) {
  if (channelID == data->channelID)
    dataBlockArray->append(data);
  else throw std::exception();
}

void ChannelBlock::sort() {
  std::sort(dataBlockArray->begin(), dataBlockArray->end(), [](const DataBlock *a, const DataBlock *b) {
    return a->blockID < b->blockID;
  });
}

double ChannelBlock::frequency() {
  return dataBlockArray ? dataBlockArray->at(0)->frequency : 0;
}

QList<Parameter *> ChannelBlock::data() {
  if (_data.length() == 0 && dataBlockArray->count() > 0) {
    sort();
    int pos = 0;
    for (DataBlock *dataBlock : *dataBlockArray) {
      double deltaIndex = ACD2File::round(1.0 / dataBlock->frequency, 3); // шаг индекса
      double deltaTime = ACD2File::round(1000 / dataBlock->frequency, 3); // шаг времени
      int f = 0;
      foreach (double value, dataBlock->data()) {
        double index = deltaIndex * pos++;
        QDateTime time = dataBlock->time.addMSecs(deltaTime * f++);
        Parameter *p = new Parameter(index, time, value);
        _data.append(p);
      }
    }
  }
  return _data;
}

DataBlockArray* ChannelBlock::array(int persecond) {
  DataBlockArray* result = nullptr;
  if (finalData.contains(persecond))
    return finalData.value(persecond);
  if (frequencies.contains(persecond)) {
    QVector<Parameter*> array = data();
    double f = frequency();
    result = new DataBlockArray(this->name, f, persecond);
    double temp = f / persecond;      // Ищем ближайший делитель
    int mod = (int)std::round(temp);  // он же шаг в буфере даных
    if (mod == 0) mod = 1;            // несущая частота меньше запрошенной
    auto repeat = (int)(1 / temp);    // число повторов значения, если частота меньше запрошенной
    if (repeat == 0) repeat = 1;
    auto deltaTime = 1000 / std::min((int)f, persecond); // шаг времени
    double index = 0;
    int position = 0;
    for (int n = 0; n < array.length(); n += mod) {
      auto parameter = array.at(n);
      auto value = mod == 1 ? parameter->value : lib::avg(array.mid(n, mod));
      for (int i = 0; i < repeat; i++) {
        auto time = parameter->time.addMSecs(deltaTime*i);
        Parameter p = Parameter(lib::increment(persecond, index), time, value);
        result->append(p);
      }
    }
    finalData[persecond] = result;
  }
  return result;
}
