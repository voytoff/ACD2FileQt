#include "channelblock.h"
#include "datablock.h"
#include "parameter.h"
#include "acd2file.h"

ChannelBlock::ChannelBlock(QObject *parent) : dataBlockArray(new QList<DataBlock*>()) {
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
}

void ChannelBlock::sort() {
  std::sort(dataBlockArray->begin(), dataBlockArray->end(), [](const DataBlock *a, const DataBlock *b) {
    return a->blockID < b->blockID;
  });
}

double ChannelBlock::frequency() {
  return dataBlockArray ? dataBlockArray->at(0)->frequency : 0;
}

QVector<Parameter *> ChannelBlock::data() {
  if (_data.length() == 0 && dataBlockArray->count() > 0) {
    sort();
    int pos = 0;
    for (DataBlock *dataBlock : *dataBlockArray) {
      double deltaIndex = ACD2File::round(1.0 / dataBlock->frequency, 3); // шаг индекса
      double deltaTime = ACD2File::round(1000 / dataBlock->frequency, 3); // шаг времени
      int zzz = 0;
      foreach (double value, dataBlock->data()) {
        double index = deltaIndex * pos++;
        QDateTime time = dataBlock->time.addMSecs(deltaTime * zzz++);
        //qDebug() << dataBlock->blockID << time.toString("dd.MM.yyyy HH.mm.ss.zzz");
        Parameter *p = new Parameter(index, time, value);
        _data.append(p);
      }
    }
  }
  return _data;
}
