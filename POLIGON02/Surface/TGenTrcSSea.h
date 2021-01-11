
              // TGenTrcSSea
#ifndef _TGENTRCSSEA_H
#define _TGENTRCSSEA_H

#include "AdjustmentCommon.h"

namespace PTPV
{

namespace sea
{
using namespace COMMON::_PTPV_;

//==========================================================================
//  Структура данных трассовой информации объекта (ВО, НВО)
//  на выходе третичной обработки
//========================================================================

struct TGenTrcT
{
  double tHold;              // вpемя хpанения формуляра обобщённой трассы 
                             // (до ее сброса) после потери трассы последним
                             // источником информации;
  EUYesNo busyState;         // признак занятости формуляра 
                             // YES - занят, NO - свободен
  unsigned char mismatSensCount; // счётчик несоответствий по количеству 
                                 // сопровождающих источников
};

struct TGenTrcS
{
	PTPV_TGenTrc genTrc;
	TGenTrcT genTrcT;
};
	
} // namespace sea

} // namespace PTPV

#endif // _TGENTRCSSEA_H
