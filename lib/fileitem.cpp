#include "fileitem.h"
#include "datablock.h"
#include "channelarray.h"
#include <QFile>
#include <QRegularExpression>

FileItem::FileItem(QObject *parent) : QObject{parent} { }

FileItem::FileItem(ChannelArray *channelBlockArray, bool deferred, QObject *parent) : FileItem(parent) {
  this->channelBlockArray = channelBlockArray;
  this->deferred = deferred;
}
FileItem::FileItem(QString fileName, int index, ChannelArray* channelBlockArray, bool deferred, QObject *parent)
  : FileItem(channelBlockArray, deferred, parent) {
  this->fileName = fileName;
  this->index = index;
}

FileACD *FileItem::file() {
  if (_file == nullptr)
    _file = new FileACD(fileName);
  return _file;
}

void FileItem::loadInfo() {
  fileIDBlock.init(file());
  headerBlock.init(file());
} // loadInfo

void FileItem::loadData() {
  int n = 0;
  QString blockType = "";
  while (blockType != hashBlockType && file()->pos() < file()->size()) {
    if (++n % 10000 == 0) break;
    //  qDebug() << n << "iteration" << file()->pos() << file()->fileName();
    blockType = file()->get<QString>(8);                        // Идентификатор структуры 8 byte
    if (blockType == channelBlockType) {
      int channelID = file()->get<int>(4);                     // Идентификатор канала 4 byte.
      if (!channelBlockArray->containsChannel(channelID)) {
        auto channelBlock = new ChannelBlock();
        channelBlock->blockType = blockType;
        channelBlock->channelID = channelID;
        channelBlock->name = trimChannelName(file()->get<QString>(128));// Имя канала 128 byte
        // дублирующий канал заканчивается в названии - _d
        channelBlock->description = file()->get<QString>(256);   // Описание канала 256 byte
        channelBlock->unit = file()->get<QString>(32);           // Единица измерения 32 byte
        channelBlock->dataType = (DataType)file()->get<int>(4);  // Тип данных 4 byte <- 420
        channelBlockArray->addChannel(channelBlock);
      } else {
        file()->seekNext(420);  // Фиктивно дочитываем данные канала 128+256+32+4
      }
    } else if (blockType == dataBlockType) {
      auto dataBlock = new DataBlock();
      dataBlock->fileItem = this;                                // Файл для чтения данных
      // Придется удерживать до завершения обработки
      // Иначе велики издержки на открытие/закрытие
      dataBlock->blockType = blockType;
      dataBlock->channelID = file()->get<int>(8);                // Идентификатор канала 8 byte
      dataBlock->blockID = file()->get<ulong>(8);                // Идентификатор блока 8 byte
      dataBlock->time = file()->get<QDateTime>(8);               // Время 8 byte
      dataBlock->timeSource = file()->get<short>(2);             // Источник времени 2 byte
      dataBlock->quality = file()->get<QString>(2);              // Качество данных 2 byte
      dataBlock->payloadSize = file()->get<int>(4);              // Размер блока в байтах 4 byte
      dataBlock->frequency = file()->get<double>(8);             // Частота дискретизации данных в блоке 8 byte
      channelBlockArray->addData(dataBlock);
      //qDebug() << dataBlock->time.toString() << dataBlock->channelID << dataBlock->blockID;
      // округляем до секунды
      dataBlock->time = channelBlockArray->setCorrection(dataBlock->time);
      if (dataBlock->payloadSize > 0) {                          // Данные
        if (deferred) {
          dataBlock->filePosition = file()->pos();               // Указатель на тело кадра в файле
          file()->seekNext(dataBlock->payloadSize);  // продвигаем указатель. Данные грузим по требованию
        } else {
          dataBlock->payload = file()->read(dataBlock->payloadSize);
          dataBlock->payloadSizeError = dataBlock->payload.length() != dataBlock->payloadSize;
        }
      }
    } else if (blockType == hashBlockType) {
      hashBlock.init(file());
    } else {
      qDebug() << n << channelBlockArray->count() << blockType << file()->pos() << file()->size() << file()->fileName() << "ERROR";
    }
  }
  fileLoaded(index, fileName);
} // loadData

QString FileItem::trimChannelName(QString rawChannelName) {
  return rawChannelName.remove(QRegularExpression(QString("%1+$").arg(channelDoubleName)));
} // trimChannelName

