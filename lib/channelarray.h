#ifndef CHANNELARRAY_H
#define CHANNELARRAY_H

#include "ACD2File_global.h"
#include "channelblock.h"
#include <QHash>
#include <QList>

/**
 * Словарь каналов
 * @brief The ChannelArray class
 */
class ACD2FILE_EXPORT ChannelArray : public QHash<int, ChannelBlock> // *
{
  public:
  ChannelArray();

  qsizetype count();

  /**
   * Знак поправки округления времени. Вычисляется на этапе загрузки первого блока.
   * Устанавливается для того, чтобы по нему округлять времена всех последующих блоков данных.
   * Используется для устранения эфекта дребезга округления около~500~миллисекундных времен.
   * @brief Correction
   */
  DateTimeRoundType correction = DateTimeRoundType::None;

  /**
   * Возвращает канальный блок по указанному фильтру
   * @brief get
   * @param predicate
   * @return
   */
  ChannelBlock* get(std::function<bool(const ChannelBlock&)> &predicate);

  /**
   * Возвращает канальный блок по указанному имени
   * @brief operator []
   * @param name
   * @return
   */
  ChannelBlock* operator[](QString name);

  /**
   * Проверяет наличие канала с именем name
   * @brief ContainsChannel
   * @param name
   * @return
   */
  bool containsChannel (QString name);
  bool containsChannel(int id);

  ChannelBlock addChannel (ChannelBlock channel);

  void addData (DataBlock *data);

  /**
   * Список канальных имен
   * @brief names
   * @return
   */
  QList<QString> names();

  /**
   * Время начала записи каналов. Время появления первого блока данных.
   * @brief start
   * @return
   */
  QDateTime start();

  /**
   * Время окончания записи каналов. Время записи последнего блока данных.
   * @brief stop
   * @return
   */
  QDateTime stop();

  QDateTime setCorrection(const QDateTime &time);
};

#endif // CHANNELARRAY_H
