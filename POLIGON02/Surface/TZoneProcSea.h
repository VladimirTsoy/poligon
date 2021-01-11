#ifndef TZONEPROCSEA_H
#define TZONEPROCSEA_H

#include "HSea.h"
#include "TGeneralTrackSea.h"

#include "UZone.h"

using namespace COMMON::_ZONE_;

#include "point_in_zone_checker.h"

namespace PTPV
{

namespace sea
{
	
// Программа расчёта попаданий объекта в зоны.
class TZoneProc
{
private:

	point_in_zone_checker zoneCalculator;
	TGeneralTrack &Trc;

public:

	//===================================================
	TZoneProc(TGeneralTrack &GeneralTrack, TZone zones[ZONE_MAX]);

	//===================================================
	// Диспетчер задач
	void MsgTaskChain(TMsgProc *pMsgProc);

	//===================================================
	// Диспетчер периодического контроля статуса
	void StateTaskChain(TStateProc *pStateProc);

}; // class TZoneProc
	
} // namespace sea

} // namespace PTPV


#endif // TZONEPROCSEA_H
