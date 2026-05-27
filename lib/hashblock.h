#ifndef HASHBLOCK_H
#define HASHBLOCK_H

#include "file.h"
#include <QString>

/**
 * Блок информации контрольной суммы файла
 * @brief The HashBlock class
 */
class HashBlock
{
  public:
  HashBlock();

  /**
   * Идентификатор структуры
   * @brief blockType
   */
  QString blockType;

  /**
   * Хеш SHA256 (256 бит), вычисленный для всего файла 32 байта
   * @brief hash
   */
  QString hash;

  void init(File *file);
};

#endif // HASHBLOCK_H
