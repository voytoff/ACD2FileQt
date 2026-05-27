#include "headerblock.h"
#include "ACD2File_global.h"

HeaderBlock::HeaderBlock() {}

void HeaderBlock::init(File *file) {
  systemID = file->get<QString>(systemIDStringSize);               // Идентификатор системы сбора данных == 32 Байта
  softwareVersion = file->get<QString>(softwareVersionStringSize); // Версия ПО (регистратор) == 16 Байт
  startTime = file->get<QDateTime>(8);                             // Время создания файла == 8 Байт (4 + 4)
  utcOffset = file->get<double>(8);                                // Смещение всех меток времени в файле от UTC+0 == 8 Байт (float занимает 4 байта + продвигаем указатель на 4 байта)
} // init
