#include "hashblock.h"
#include "ACD2File_global.h"

HashBlock::HashBlock() {}

void HashBlock::init(FileACD *file) {
  blockType = hashBlockType;
  hash = file->get<QString>(32);
} // init
