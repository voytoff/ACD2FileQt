#ifndef ACD2FILE_GLOBAL_H
#define ACD2FILE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QString>

#if defined(ACD2FILE_LIBRARY)
#define ACD2FILE_EXPORT Q_DECL_EXPORT
#else
#define ACD2FILE_EXPORT Q_DECL_IMPORT
#endif

const QString ext_acd = ".acd";
const QString pattern_acd = "*.acd";
/**
 * окончание в названии дублирующих каналов телеметрии
 * @brief channelDoubleName
 */
const QString channelDoubleName = "_d";

enum DateTimeRoundType: int {
  None = 2,
  EQ = 0,
  LT = -1,
  GT = 1,
}; // DateTimeRoundType

enum AxisXType : int {
  Index = 1,
  Time = 2,
};

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
