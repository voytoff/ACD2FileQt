#include "datablock.h"
#include "channelblock.h"

DataBlock::DataBlock(QObject *parent) {}

QByteArray DataBlock::getPayload() {
  if (payload.length() == 0 && payloadSize > 0)
    payload = fileItem->file()->readExt(filePosition, payloadSize);
  return payload;
}

QVector<double> DataBlock::data() {
  if (_data == nullptr && payloadSize > 0) {
    _data = new QVector<double>();
    auto p = getPayload();
    if (p.length() > 0) {
      int len = dtLength(channel->dataType);
      int count = p.length() / len;
      _data->resize(count);
      for (int n = 0; n < count; n++) {
        int current = n * len;
        QByteArray sub = p.mid(current, len);
        float value;
        std::memcpy(&value, sub.constData(), len);
        (*_data)[n] = value;
      }
    };
  }
  return _data == nullptr ? QVector<double>() : *_data;
}

const int DataBlock::dtLength(const DataType value) {
  switch(value ) {
    case acdtInt16:   return 2;
    case acdtFloat:   return 4;
    case acdtDouble:  return 8;
    case acdtUChar:   return 4;
    case acdtUInt32:  return 4;
    case acdtTime:    return 4;
    default:          return 4;
  }
}
