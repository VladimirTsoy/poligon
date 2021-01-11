#include "TPrognProcAir.h"

namespace PTPV
{
	
namespace air
{

//===================================================
TPrognProc::TPrognProc(TGeneralTrack &GeneralTrack)
         : Trc(GeneralTrack)
{} // TPrognProc()

//===================================================
// Диспетчер задач
void TPrognProc::MsgTaskChain(TMsgProc *const pMsgProc)
{
	for ( int i = 0; i < 2; i++ )
		if ( pMsgProc->Update[i].xyUpdate )
		{
			// Экстраполяция координат обобщённой трассы относительно
			// момента их последнего обновления на заданный промежуток времени.
			// ...
			PTPV_TGenTrc &GenTrc = Trc[pMsgProc->Update[i].trcNum].genTrc;
			GenTrc.progn.x = GenTrc.x + GenTrc.vX * 60.F;
			GenTrc.progn.y = GenTrc.y + GenTrc.vY * 60.F;
		} // if
} // MsgTaskChain()

//===================================================
// Диспетчер периодического контроля статуса
void TPrognProc::StateTaskChain(TStateProc *const pStateProc)
{} // StateTaskChain()

} // namespace air

} // namespace PTPV
