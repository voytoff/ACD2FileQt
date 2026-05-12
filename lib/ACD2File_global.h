#ifndef ACD2FILE_GLOBAL_H
#define ACD2FILE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QString>

#if defined(ACD2FILE_LIBRARY)
#define ACD2FILE_EXPORT Q_DECL_EXPORT
#else
#define ACD2FILE_EXPORT Q_DECL_IMPORT
#endif

const QString Ext = ".acd";
const QString Pattern = "*.acd";
/**
 * окончание в названии дублирующих каналов телеметрии
 * @brief channelDoubleName
 */
const QString channelDoubleName = "_d";

enum DataType: int {
  none = 0     /*Ошибка*/,
  acdtInt16   = 8194  /*0x2002*/,
  acdtFloat   = 8196  /*0x2004*/,
  acdtDouble  = 12288 /*0x3000*/,
  acdtUChar   = 8199  /*0x2007*/,
  acdtUInt32  = 8197  /*0x2005*/,
  acdtTime    = 12293 /*0x3005*/
}; // enum DataType

enum DateTimeRoundType {
  None = 2,
  EQ = 0,
  LT = -1,
  GT = 1,
}; // DateTimeRoundType

const QString formatIDString          = "ACD2";
const QString formatVersionString     = "1.0";

const QString channelBlockType        = "CHBLOCK";
const QString dataBlockType           = "DTBLOCK";
const QString hashBlockType           = "HASH";

const int idStringSize                = 8;
const int versionStringSize           = 8;
const int blockTypeStringSize         = 8;
const int systemIDStringSize          = 32;
const int softwareVersionStringSize   = 16;
const int hashSize                    = 32;

const int channelNameSize             = 128;
const int channelDescriptionSize      = 256;
const int channelUnitSize             = 32;

#endif // ACD2FILE_GLOBAL_H
