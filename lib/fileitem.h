#ifndef FILEITEM_H
#define FILEITEM_H
#pragma once

#include "file.h"
//#include "channelarray.h"
#include "fileidblock.h"
#include "hashblock.h"
#include "headerblock.h"
#include <QObject>
#include <QFile>
#include <QStringConverter>

class ChannelArray;

/**
 * Класс для работы с одним файлом acd версии 2<br/>
 * - Возможность хранения меток времени от СЕВ, по одной метке на каждый блок каждого канала;<br/>
 * - Возможность хранения признака качества данных;<br/>
 * - Возможность хранения идентификатора блока данных для определения пропусков и дублирования кадров;<br/>
 * - Файл может быть прочитан последовательно из начала в конец без танцев с бубном;;<br/>
 * - Файл может одержать любое количество блоков данных и любое количество каналов.
 *   Разные каналы могут иметь разное количество блоков данных;<br/>
 * - Блоки данных могут иметь переменную во времени длину.<br/>
 * <i>Для компилятора C++ все структуры хранятся со стандартным выравниванием - 8 байт</i>
 * @brief The FileItem class
 */
class FileItem : public QObject {
  Q_OBJECT

public:
  explicit FileItem(QObject *parent = nullptr);
  explicit FileItem(ChannelArray* channelBlockArray, bool deferred = true, QObject *parent = nullptr);
  explicit FileItem(QString fileName, int index, ChannelArray* channelBlockArray, bool deferred = true, QObject *parent = nullptr);

  /**
   * Номер файла в списке
   * @brief index
   */
  int index;

  /**
   * Блок информации идентификатора файла = 16 byte
   * @brief fileIDBlock
   */
  FileIDBlock fileIDBlock;

  /**
   * Блок информации о заголовке файла = 64 byte
   * @brief headerBlock
   */
  HeaderBlock headerBlock;

  /**
   * Блок информации контрольной суммы файла = 40 байт
   * @brief hashBlock
   */
  HashBlock hashBlock;

  /**
   * Флаг отложенной загрузки буфера данных. Если установлен,
   * сохраняется указатель на начало блока в DataBlock.FilePosition,
   * который используется в момент востребованности данных
   * @brief deferred
   */
  bool deferred;

  /**
   * Массив блоков информации по каналам. Пробрасывается в FileItem для загрузки данных из файлов
   * @brief channelBlockArray
   */
  ChannelArray* channelBlockArray;

  /**
   * Имя файла данных acd2
   * @brief fileName
   */
  QString fileName;

  /**
   * Файл
   * @brief file
   * @return
   */
  File* file();

private:

  File* _file = nullptr;

  /**
   * Убирает из названия канала окончание (признак _d) дублера
   * @brief trimChannelName
   * @param rawChannelName
   * @return
   */
  QString trimChannelName (QString rawChannelName);

public slots:
  /**
   * Загружает заголовки файла
   * @brief loadInfo
   */
  void loadInfo();

  /**
   * Загружает данные файла
   * @brief loadData
   */
  void loadData();

signals:
  /**
   * Сигнализирует о прочтении очередного блока канала
   * @brief channelBlockRead
   */
  void channelBlockRead(QString fileName, int channelID, QString name);
  /**
   * Сигнализирует о прочтении очередного блока данных
   * @brief dataBlockRead
   */
  void dataBlockRead(QString fileName, int channelID, int blockID, int size);
  /**
   * Сигнализирует об окончании операции загрузки данных
   * @brief fileLoaded
   */
  void fileLoaded(int index, QString fileName); // Signal declaration
};

#endif // FILEITEM_H
