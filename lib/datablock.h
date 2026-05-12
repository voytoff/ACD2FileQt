#ifndef DATABLOCK_H
#define DATABLOCK_H

#include "ACD2File_global.h"
#include "fileitem.h"
#include <QDateTime>

class ChannelBlock;

class DataBlock
{

public:
  explicit DataBlock();

  /**
   * Идентификатор структуры
   * @brief blockType
   */
  QString blockType;

  /**
   * Файл, в котором находятся данные этого блока канала
   * @brief fileItem
   */
  FileItem* fileItem;

  /**
   * Время в формате FILETIME, со смещеним UTC+0, соотвтсвующее моменту плучеия первого значения в блоке данных = 8 byte
   * @brief time
   */
  QDateTime time;

  /**
   * Источник времени, может принимать значения, описанные в перечислении ChannelTimeSource = 2 byte
   * @brief timeSource
   */
  short timeSource;

  /**
   * Качество данных. Зарезервировано = 2 byte
   * @brief quality
   */
  QString quality;

  /**
   * Размер блока данных в байтах. Количество значений данных можно получить, разделив payloadSize
   * на размер одного значения типа данных канала. 4 байта
   * @brief payloadSize
   */
  int payloadSize;

  /**
   * Данные как есть в файле без преобразований
   * @brief payload
   */
  QByteArray payload;

  /**
   * Частота дискретизации данных в блоке Гц
   * @brief frequency
   */
  double frequency;

  /**
   * Указатель на данные в файле
   * @brief filePosition
   */
  long filePosition;

  /**
   * Ошибка, возникающая при несоответствии объявленной длины данных payloadSize и фактической длины прочитанных данных
   * @brief payloadSizeError
   */
  bool payloadSizeError;

  /**
   * Идентификатор канала, к которому относится этот блок данных = 4 байт
   * @brief channelID
   */
  int channelID;

  /**
   * Идентификатор блока данных. В нормальных условиях должен последовательно возрастать.
   * Если не так, значит произошло дублирование или потеря данных. 8 байт
   * @brief blockID
   */
  ulong blockID;

  /**
   * Указатель на блок канала
   * @brief channel
   */
  ChannelBlock* channel;


  QByteArray getPayload();

  QVector<double> data();

private:
  const int dtLength (const DataType value);
  QVector<double> _data;

};

#endif // DATABLOCK_H
