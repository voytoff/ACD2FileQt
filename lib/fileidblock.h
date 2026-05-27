#ifndef FILEIDBLOCK_H
#define FILEIDBLOCK_H

#include "file.h"
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

  void init(File *file);
};

#endif // FILEIDBLOCK_H
