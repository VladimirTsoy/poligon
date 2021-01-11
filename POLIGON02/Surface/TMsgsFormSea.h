#ifndef _TMSGSFORMSEA_H
#define _TMSGSFORMSEA_H

#include "AdjustmentCommon.h"
#include "HSeaFAL.h"
#include "HSea.h"
#include "TGeneralTrackSea.h"

namespace PTPV
{

namespace sea
{
using namespace COMMON::_PTPV_;

class TMsgsForm
{
private:
	struct TGenTrcMsg;     // тип сообщения с обобщённой трассой

	TGeneralTrack &Trc;

	TCountKeep CountKeep;

private:
	// Формирование заголовка PTPV_Msg_Sea
	void FormTrcMsgHdr(PTPV_TGenTrcMsg *pGenTrcMsg, double currentT);
	
public:
	TMsgsForm(TGeneralTrack &GeneralTrack);
	~TMsgsForm(void);

	// Формирование выходных сообщений по рез-там обработки поступивших данных
	void operator() (double T, const TMsgProc *pMsgProc,
	                 PTPV_TGenTrcMsg *pGenTrcMsg, TMsgFormSet *pmsgFormSet);
	
	// Формирование признаков отсутствия выходных сообщений
	void operator() (TMsgFormSet *pmsgFormSet);
	
	// Формир-ние выходного сообщения по рез-там периодической обработки данных
	void operator() (double T, const TStateProc *pStateProc,
	                 PTPV_TGenTrcMsg *pGenTrcMsg, TMsgFormSet *pmsgFormSet);

}; // class TMsgsForm

} // namespace sea

} // namespace PTPV

#endif // _TMSGSFORMSEA_H
