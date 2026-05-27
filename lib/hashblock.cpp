#include "hashblock.h"
#include "ACD2File_global.h"

HashBlock::HashBlock() {}

void HashBlock::init(File *file) {
  blockType = hashBlockType;
  hash = file->get<QString>(32);
} // init
