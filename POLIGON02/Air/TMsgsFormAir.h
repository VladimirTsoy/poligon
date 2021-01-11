#ifndef _TMSGSFORMAIR_H
#define _TMSGSFORMAIR_H

#include "AdjustmentCommon.h"
#include "HAirFAL.h"
#include "HAir.h"
#include "TGeneralTrackAir.h"
// #include "WP.h"

namespace PTPV
{

namespace air
{
using namespace _PTPV_;

class TMsgsForm
{
private:
	struct TGenTrcMsg;     // тип сообщения с обобщённой трассой

	TGeneralTrack &Trc;

	TCountKeep CountKeep;
	
private:
	// Формирование заголовка PTPV_Msg_Air
	void FormTrcMsgHdr(PTPV_TGenTrcMsg* pGenTrcMsg, double currentT);
	
public:
	TMsgsForm(TGeneralTrack &GeneralTrack);
	~TMsgsForm(void);

	// Формирование выходного сообщения
	void operator() (unsigned char sensNum, const TUMsgHdr &Msg, double T,
	                 const TMsgProc *pMsgProc,
	                 PTPV_TGenTrcMsg *pGenTrcMsg, TMsgFormSet *pmsgFormSet);
	
	// Формирование выходного сообщения... ?
	void operator() (TMsgFormSet *pmsgFormSet);
	
	// Формир-ние выходного сообщения по рез-там периодической обработки данных
	void operator() (double T, const TStateProc *pStateProc, TUTrcMsg *pOrderSP,
	                 PTPV_TGenTrcMsg *pGenTrcMsg, TMsgFormSet *pmsgFormSet);
	
}; // class TMsgsForm

} // namespace air

} // namespace PTPV

#endif // _TMSGSFORMAIR_H
