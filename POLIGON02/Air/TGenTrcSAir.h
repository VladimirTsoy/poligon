         
              // TGenTrcSAir
#ifndef _TGENTRCSAIR_H
#define _TGENTRCSAIR_H

#include "AdjustmentCommon.h"

namespace PTPV
{

namespace air
{
using namespace COMMON::_PTPV_;

//==========================================================================
//  Структура данных трассовой информации объекта (ВО, НВО)
//  на выходе третичной обработки
//========================================================================
	
struct TGenTrcT
{
  double tHold;              // вpемя хpанения формуляра обобщённой трассы 
                             // (до её сброса) после потери трассы последним
                             // источником информации;
  double tMsg;               // вpемя выдачи обобщённой трассы 
                             // по донесению источника
  EUYesNo busyState;         // признак занятости формуляра
                                        // EU_YES - занят, EU_NO - свободен
  unsigned char mismatSensCount; // счётчик несоответствий по количеству 
                                 // сопровождающих источников
};

struct TGenTrcS
{
	PTPV_TGenTrc genTrc;
	TGenTrcT genTrcT;
};
	
} // namespace air

} // namespace PTPV

#endif // _TGENTRCSAIR_H
