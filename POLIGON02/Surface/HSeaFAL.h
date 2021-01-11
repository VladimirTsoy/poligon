// Структуры, используемые одновременно в интерфейсе и реализации
// функциональной задачи обработки информации по НПО.

#ifndef _HSEAFAL_H
#define _HSEAFAL_H

#include "AdjustmentCommon.h"
#include "TGeneralTrackSea.h"

namespace PTPV
{

namespace sea
{

	// набор признаков формирования сообщений потребителям по рез-там обработки
	struct TMsgFormSet
	{
		bool genTrcMsg[2];  // информация двух обобщённых трасс (А и Б)
	}; // TMsgFormSet

} // namespace sea

} // namespace PTPV

#endif // _HSEAFAL_H
