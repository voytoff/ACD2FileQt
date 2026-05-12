#include "ACD2File_global.h"
#include "channelarray.h"
#include "datablock.h"

// QHash<int, ChannelBlock>
ChannelArray::ChannelArray() {}

qsizetype ChannelArray::count() {
  return QHash::count();
}

ChannelBlock *ChannelArray::get(std::function<bool (const ChannelBlock &)> &predicate) {
  auto it = std::find_if(this->begin(), this->end(), predicate);
  return &it.value();
}

ChannelBlock *ChannelArray::operator[](QString name) {
  std::function<bool(const ChannelBlock&)> func = [name](const ChannelBlock& item) {return item.name == name;};
  auto it = get(func);
  return it;
}

bool ChannelArray::containsChannel(QString name) {
  return (*this)[name] != nullptr;
} // containsChannel

bool ChannelArray::containsChannel(int id) {
  return this->contains(id);
} // containsChannel

ChannelBlock ChannelArray::addChannel(ChannelBlock channel) {
  if (!contains(channel.channelID)) this->insert(channel.channelID, channel);
  return channel;
} // addChannel

void ChannelArray::addData(DataBlock* data) {
  ChannelBlock channel = this->value(data->channelID);
  channel.add(data);
  // Запишем данные канала в блок данных
  data->channel = &channel;
} // addData

QList<QString> ChannelArray::names() {
  QList<QString> result;
  result.reserve(this->size());
  std::transform(this->begin(), this->end(), std::back_inserter(result), [](ChannelBlock x) { return x.name; });
  return result;
}

QDateTime ChannelArray::start() {
  auto it = std::min_element(values().begin(), values().end(), [](ChannelBlock &a, ChannelBlock &b) {
    auto x = a.start();
    auto y = b.start();
    return x < y;
  });
  return it->start();
}

QDateTime ChannelArray::stop() {
  auto it = std::max_element(values().begin(), values().end(), [](ChannelBlock &a, ChannelBlock &b) {
    auto x = a.stop();
    auto y = b.stop();
    return x > y;
  });
  return it->stop();
}

QDateTime ChannelArray::setCorrection(const QDateTime &time) {
  auto c = qAbs(time.toMSecsSinceEpoch() % 1000);
  QDateTime result = time.addMSecs(-c);
  if (correction == DateTimeRoundType::None) {
    correction = c < 500 ? DateTimeRoundType::LT : c > 500 ? DateTimeRoundType::GT : DateTimeRoundType::EQ;
  }
  return correction == DateTimeRoundType::GT ? result.addSecs(1) : result;
} // setCorrection
