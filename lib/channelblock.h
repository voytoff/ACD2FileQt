#ifndef CHANNELBLOCK_H
#define CHANNELBLOCK_H

#include "ACD2File_global.h"
#include "datablock.h"
#include "parameter.h"
#include <QString>
#include <QList>
#include <QDateTime>

//class DataBlock;
class ACD2FILE_EXPORT ChannelBlock : public QObject {
  Q_OBJECT

  public:
  ChannelBlock(QObject *parent = nullptr);

  bool operator==(const ChannelBlock &other) const {
    return channelID == other.channelID && name == other.name;
  }
  bool operator<(const ChannelBlock &other) const {
    return channelID < other.channelID;
  }

  /**
   * Идентификатор структуры
   * @brief blockType
   */
    QString blockType;

  /**
   * Строка с идентификатором структуры (всегда содержит значение Constants.ChannelBlockType).
   * Преднозначена для того, чтобы отличать заголовки каналов от заголовков блоков данных.
   * 8 байт
   * @brief BlockType
   */
  QString BlockType;

  /**
   * Числовой идентификатор канала в файле, должен быть уникальным для каждого канала.
   * Допустимо записывать сюда номера каналов в файле, например, 1, 2 ,3 и т.д.
   * Однако, последовательность записи блоков данных и заголовков в файл необязательно будет
   * совпадать с последовательностью ChannelID. Рекомендуется также сохранять ChannelID для канала
   * неизменными в пределах файлов одной одной группы (ри многофайловой регистрации данных).
   * 4 байта
   * @brief channelID
   */
  int channelID;

  /**
   * Имя канала = 128 byte
   * @brief name
   */
  QString name;

  /**
   * Развернутое описание канала
   * @brief description
   */
  QString description;

  /**
   * Единица измерения
   * @brief unit
   */
  QString unit;

  /**
   * Тип данных канала
   * @brief dataType
   */
  DataType dataType;

  /**
   * Массив считанных блоков данных, соответствующих этому каналу
   * @brief dataBlockArray
   */
  QList<DataBlock*>* dataBlockArray;

  /**
   * Время начала записи канала. Время появления первого кадра.
   * @brief getStart
   * @return
   */
  QDateTime start();

  /**
   * Время окончания записи канала. Время записи последнего кадра.
   * @brief stop
   * @return
   */
  QDateTime stop();

  /**
   * Добавляет блок данных в канал
   * @brief add
   * @param data
   */
  void add (DataBlock *data);

public slots:
  void sort();
  double frequency();
  /**
   * Массив с данными этого канала. Формируется из данных всех блоков
   * @brief data
   * @return
   */
  QList<Parameter*> data();
  DataBlockArray* array(int persecond);

private:
  QList<Parameter*> _data;
  QHash<int, DataBlockArray*> finalData;
  double avg(QList<Parameter*> mid);
  double increment(int persecond, double &index, int digits = 3);

};

#endif // CHANNELBLOCK_H
