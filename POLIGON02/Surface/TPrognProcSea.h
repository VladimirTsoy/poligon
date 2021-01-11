#ifndef TPROGNPROCSEA_H
#define TPROGNPROCSEA_H

#include "HSea.h"
#include "TGeneralTrackSea.h"

namespace PTPV
{

namespace sea
{
	
// Программа прогнозирования будущего положения воздушного объекта.
class TPrognProc
{
private:

	TGeneralTrack &Trc;

public:

	//===================================================
	TPrognProc(TGeneralTrack &GeneralTrack);

	//===================================================
	// Диспетчер задач
	void MsgTaskChain(TMsgProc *pMsgProc);

	//===================================================
	// Диспетчер периодического контроля статуса
	void StateTaskChain(TStateProc *pStateProc);

}; // class TPrognProc
	
} // namespace sea

} // namespace PTPV


#endif // TPROGNPROCSEA_H
