#ifndef ACDOBJECT_H
#define ACDOBJECT_H

#include "channelarray.h"
#include "fileitem.h"
#include <QObject>
#include <QList>
#include <QString>

/**
 * Класс для массива файлов обработки
 * @brief The ACDObject class
 */
class ACD2FILE_EXPORT ACDObject : public QObject {
  Q_OBJECT

  public:
  explicit ACDObject(QObject *parent = nullptr);
  explicit ACDObject(QStringList fileNames, QObject *parent = nullptr);

  /**
   * Массив файлов обработки acd2
   * @brief files
   */
  QList<FileItem*>* files;

  /**
   * Массив блоков информации по каналам.
   * Передается последовательно в конструкторы обработчиков файлов
   * и в них формируется. Пока все происходит синхронно
   * @brief channels
   */
  ChannelArray* channels;

  /**
   * Возвращает канал по его имени
   * @brief operator []
   * @param name
   * @return
   */
  ChannelBlock* operator[](QString name);

  /**
   * Проверяет наличие канала с именем name
   * @brief containsChannel
   * @param name
   * @return
   */
  bool containsChannel (QString name);

  /**
   * Время начала записи канала. Время появления первого кадра.
   * @brief start
   * @return
   */
  QDateTime start();

  /**
   * Время окончания записи канала. Время записи последнего кадра.
   * @brief stop
   * @return
   */
  QDateTime stop();

public slots:
  void load();
  void close();

signals:
  /**
   * Сигнализирует об окончании операции загрузки данных
   * @brief fileLoaded
   * @param index
   * @param fileName
   */
  void fileLoaded(int index, QString fileName); // Загружен очередной файл

  private:
};

#endif // ACDOBJECT_H
