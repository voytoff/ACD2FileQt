#include "fileidblock.h"

FileIDBlock::FileIDBlock() {}

void FileIDBlock::init(FileACD *file) {
  formatID = file->get<QString>(8);          // Идентификатор формата == 8 Байт
  formatVersion = file->get<QString>(8);     // Версия формата == 8 Байт
}
