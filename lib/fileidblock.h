#ifndef FILEIDBLOCK_H
#define FILEIDBLOCK_H

#include "fileacd.h"
#include <QString>

class FileIDBlock
{
  public:
  FileIDBlock();
  /**
   * Идентификатор формата, 8 байт
   * @brief formatID
   */
  QString formatID;
  /**
   * Версия формата, 8 байт
   * @brief formatVersion
   */
  QString formatVersion;

  void init(FileACD *file);
};

#endif // FILEIDBLOCK_H
