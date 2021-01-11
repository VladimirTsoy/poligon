#ifndef POI_H
#define POI_H

#include <QDebug>

#include <cstring>

#include "_IMIT_.h"
#include "U_PTPV_.h"

using namespace COMMON::_IMIT_;
using namespace COMMON::_PTPV_;

class Poi
{
public:
    Poi();

    static void PackMsg(const TPubEtalon &pPubEtalon, const TMsgTrc &tMsgTrc, TUTrcMsg *Msg, double T);
};

#endif // POI_H
