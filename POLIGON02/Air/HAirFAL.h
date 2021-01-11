// Структуры, используемые одновременно в интерфейсе и реализации
// функциональной задачи обработки информации по ВО.

#ifndef _HAIRFAL_H
#define _HAIRFAL_H

#include "AdjustmentCommon.h"
#include "TGeneralTrackAir.h"

namespace PTPV
{

namespace air
{

	// набор признаков формирования сообщений потребителям по рез-там обработки
	struct TMsgFormSet
	{
		bool genTrcMsg[2];  // информация двух обобщённых трасс (А и Б)
		bool orderSP[2];    // распоряжения на ВОИ, соответствующие А и Б
	}; // TMsgFormSet

} // namespace air

} // namespace PTPV

#endif // _HAIRFAL_H
