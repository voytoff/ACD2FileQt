#include "datablock.h"
#include "channelblock.h"

DataBlock::DataBlock(QObject *parent) {}

QByteArray DataBlock::getPayload() {
  if (payload.length() == 0 && payloadSize > 0)
    payload = fileItem->file()->readExt(filePosition, payloadSize);
  return payload;
}

QVector<double> DataBlock::data() {
  if (rawData == nullptr && payloadSize > 0) {
    rawData = new QVector<double>();
    auto p = getPayload();
    if (p.length() > 0) {
      int len = elementLength(channel->dataType);  // длина элемента
      int count = p.length() / len;             // число элементов
      rawData->resize(count);
      for (int n = 0; n < count; n++) {
        int current = n * len;
        QByteArray sub = p.mid(current, len);
        if (len == 4) {
          float value;
          std::memcpy(&value, sub.constData(), len);
          (*rawData)[n] = value;
        } else if (len == 8) {
          double value;
          std::memcpy(&value, sub.constData(), len);
          (*rawData)[n] = value;
        } else throw std::exception(); // неверна длина
      }
    };
  }
  return rawData == nullptr ? QVector<double>() : *rawData;
}

const int DataBlock::elementLength(const DataType value) {
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
