#include "mathd.h"
#include "TZoneProcSea.h"

namespace PTPV
{
	
namespace sea
{

//===================================================
TZoneProc::TZoneProc(TGeneralTrack &GeneralTrack, TZone zones[ZONE_MAX])
         : Trc(GeneralTrack)
{
	zoneCalculator.set_Zone(zones);
} // TZoneProc()

//===================================================
// Диспетчер задач
void TZoneProc::MsgTaskChain(TMsgProc *const pMsgProc)
{
	using namespace androsor;
	for ( int i = 0; i < 2; i++ )
		if ( pMsgProc->Update[i].xyUpdate )
		{
			PTPV_TGenTrc &GenTrack = Trc[pMsgProc->Update[i].trcNum].genTrc;
			zoneCalculator.ret_b_point_in_zone(froundi(GenTrack.x),
			    froundi(GenTrack.y), GenTrack.zones);
			zoneCalculator.ret_b_point_in_zone(froundi(GenTrack.progn.x), 
			    froundi(GenTrack.progn.y), GenTrack.progn.zones);
		} // if
} // MsgTaskChain()

//===================================================
// Диспетчер периодического контроля статуса
void TZoneProc::StateTaskChain(TStateProc *const pStateProc)
{} // StateTaskChain()

} // namespace sea

} // namespace PTPV
