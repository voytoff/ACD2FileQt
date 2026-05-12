#ifndef HEADERBLOCK_H
#define HEADERBLOCK_H
#include "fileacd.h"
#include <QString>
#include <QDateTime>

/**
 * Блок информации о заголовке файла
 * @brief The HeaderBlock class
 */
class HeaderBlock
{
  public:
  HeaderBlock();

  /**
   * Идентификатор или название системы сбора данных, только для отобраения пользователю ри чтнии файла, могут быть записаны любые данные
   * @brief systemID
   */
  QString systemID;

  /**
   * Версия ПО (регистратора) = 16 byte
   * @brief softwareVersion
   */
  QString softwareVersion;

  /**
   * Время создания/(начала записи) файла в формате FILETIME с нулевым смещением от UTC (UTC+0).
   * Это время не связано с временем получения данных в файле.
   * 8 byte
   * @brief startTime
   */
  QDateTime startTime;

  /**
   * Смещение всех меток времени в файле от UTC+0, в часах = 4 -> 8 byte
   * @brief utcOffset
   */
  float utcOffset;

  void init(FileACD *file);
};

#endif // HEADERBLOCK_H
