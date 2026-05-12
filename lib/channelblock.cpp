#include "channelblock.h"
#include "datablock.h"

ChannelBlock::ChannelBlock() {}

QDateTime ChannelBlock::start() {
  return (dataBlockArray.count() == 0) ?
           QDateTime() :
           (*std::min_element(dataBlockArray.begin(), dataBlockArray.end(), [](const DataBlock *a, const DataBlock *b) {
             return a->time < b->time;
                                                       }))->time;
}

QDateTime ChannelBlock::stop() {
  return (dataBlockArray.count() == 0) ?
           QDateTime() : // ??
           (*std::max_element(dataBlockArray.begin(), dataBlockArray.end(), [](const DataBlock* a, const DataBlock* b) {
             return a->time < b->time;
           }))->time;
}

void ChannelBlock::add(DataBlock* data) {
  if (channelID == data->channelID)
    dataBlockArray.append(data);
}
