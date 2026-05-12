#include "datablock.h"
#include "channelblock.h"

DataBlock::DataBlock() {}

QByteArray DataBlock::getPayload()
{
  if (payload.length() == 0 && payloadSize > 0)
    payload = fileItem->file()->read(payloadSize);
  return payload;
}

QVector<double> DataBlock::data() {
  if (_data.length() == 0 && payloadSize > 0) {
    auto p = getPayload();
    if (p.length() > 0) {
      int len = dtLength(channel->dataType);
      int count = p.length() / len;
      for (int n = 0; n < count; n++) {
        int current = n * len;
        auto sub = p.mid(current, len);
        double value;
        std::memcpy(&value, sub.constData(), 8);
        _data.append(value);
      }
    };
  }
  return _data;
}

const int DataBlock::dtLength(const DataType value) {
  switch(value ) {
  case acdtInt16: return 2;
  case acdtFloat: return 4;
  case acdtDouble: return 8;
  case acdtUChar: return 4;
  case acdtUInt32: return 4;
  case acdtTime: return 4;
  default: return 4;
  }
}
