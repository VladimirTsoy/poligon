#ifndef TPROGNPROCAIR_H
#define TPROGNPROCAIR_H

#include "HAir.h"
#include "TGeneralTrackAir.h"

namespace PTPV
{

namespace air
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
	
} // namespace air

} // namespace PTPV


#endif // TPROGNPROCAIR_H
