#include <float.h>

#include "TMsgsFormAir.h"

namespace PTPV
{

namespace air
{

struct TMsgsForm::TGenTrcMsg : public PTPV_TGenTrcMsg
{
	TGenTrcMsg() {}

	static const TGenTrcMsg CGenTrcMsg0;
}; // struct TGenTrcMsg


TMsgsForm::TMsgsForm(TGeneralTrack &GeneralTrack)
         : Trc(GeneralTrack)
{
	// обнуление счётчиков сообщений
	CountKeep.PTPV_Msg_Air = 0;
	CountKeep.tPeriod = 0.;
} // TMsgsForm()

TMsgsForm::~TMsgsForm(void)
{}

// Формирование выходного сообщения
void TMsgsForm::operator() (unsigned char sensNum, const TUMsgHdr &Msg,
	                        double T, const TMsgProc *pMsgProc,
	                        PTPV_TGenTrcMsg *pGenTrcMsg,
                            TMsgFormSet *pmsgFormSet)
{
	for ( int i = 0; i < 2; i++ )
	{
		const int genTrcNum = pMsgProc->Update[i].trcNum;
		const bool genTrcChange = pMsgProc->Update[i].trcUpdate ||
		   pMsgProc->Update[i].sensAdd || pMsgProc->Update[i].sensDelete;
		   
		/* Формир-ние обобщённой трассовой инф-ции объекта потребителям ТОИ. */
		if ( genTrcChange )
		{
			TGenTrcS &GenTrack = Trc[genTrcNum];

			pGenTrcMsg[i] = TGenTrcMsg::CGenTrcMsg0;
			
			pGenTrcMsg[i].genTrcNum = genTrcNum;
			if ( pMsgProc->Update[i].newTrc != 0 )
				pGenTrcMsg[i].trcState = EU_TS_NEW;
			else
				pGenTrcMsg[i].trcState = EU_TS_TRK;
			if ( pMsgProc->Update[i].sensAdd == EU_YES )
				pGenTrcMsg[i].sensAdd = EU_YES;
			else
				pGenTrcMsg[i].sensAdd = EU_NO;
			if ( pMsgProc->Update[i].sensDelete == EU_YES )
				pGenTrcMsg[i].sensDelete = EU_YES;
			else
				pGenTrcMsg[i].sensDelete = EU_NO;
						
			pGenTrcMsg[i].trc = GenTrack.genTrc;

			if ( pMsgProc->Update[i].trcUpdate )
			{
				pGenTrcMsg[i].xyUpdate = pMsgProc->Update[i].xyUpdate;
				pGenTrcMsg[i].hUpdate = pMsgProc->Update[i].hUpdate;
				pGenTrcMsg[i].ogpUpdate = pMsgProc->Update[i].OGPUpdate;
			} // if trcUpdate

			GenTrack.genTrcT.tMsg = T;
			
			FormTrcMsgHdr(pGenTrcMsg + i, T);
		} // if genTrcChange
		pmsgFormSet->genTrcMsg[i] = genTrcChange;

		pmsgFormSet->orderSP[i] = false;

	} // for (i) { pMsgProc->Update[i].trcNum }
} // FormGenTrcMsg()

// Формирование выходного сообщения... ?
void TMsgsForm::operator() (TMsgFormSet *pmsgFormSet)
{
	pmsgFormSet->genTrcMsg[0] = pmsgFormSet->genTrcMsg[1]  =
	pmsgFormSet->orderSP[0] = pmsgFormSet->orderSP[1] = false;
} // FormGenTrcMsg()

// Формирование выходного сообщения по рез-там периодической обработки данных
void TMsgsForm::operator() (double T, const TStateProc *pStateProc,
                            TUTrcMsg *pOrderSP, PTPV_TGenTrcMsg *pGenTrcMsg,
                            TMsgFormSet *pmsgFormSet)
{
	const int genTrcNum = pStateProc->genTrcNum;
	
	const bool genTrcChange = pStateProc->sensTrcDrop || pStateProc->genTrcDrop;

	/* Формир-ние обобщённой трассовой инф-ции объекта потребителям ТОИ. */
	if ( genTrcChange )
	{
		TGenTrcS &GenTrack = Trc[genTrcNum];
		
		*pGenTrcMsg = TGenTrcMsg::CGenTrcMsg0;
		
		pGenTrcMsg->genTrcNum = genTrcNum;
		if ( pStateProc->genTrcDrop )
			pGenTrcMsg->trcState = EU_TS_END;
		else
			pGenTrcMsg->trcState = EU_TS_TRK;
		if ( pStateProc->sensTrcDrop )
			pGenTrcMsg->sensDelete = EU_YES;
		else
			pGenTrcMsg->sensDelete = EU_NO;
		pGenTrcMsg->trc = GenTrack.genTrc;
		
		FormTrcMsgHdr(pGenTrcMsg, T);
		pmsgFormSet->genTrcMsg[0] = true;
	} // if genTrcChange
	else
		pmsgFormSet->genTrcMsg[0] = false;
		
		pmsgFormSet->orderSP[0] = false;

} // FormGenTrcMsg()


// Формирование заголовка PTPV_Msg_Air
void TMsgsForm::FormTrcMsgHdr(PTPV_TGenTrcMsg* pGenTrcMsg, double currentT)
{
	// идентификатор типа сообщения
	pGenTrcMsg->msgType = EU_MT_PTPV_AIR;
	// длина передаваемого сообщения в байтах, включая длину заголовка
	pGenTrcMsg->msgLength = sizeof(PTPV_TGenTrcMsg);
	// время отправки сообщения
	pGenTrcMsg->msgTime = currentT;
	// порядковый номер сообщения от соответствующей программы-отправителя
	CountKeep.PTPV_Msg_Air++;
	pGenTrcMsg->msgNum = CountKeep.PTPV_Msg_Air;
	// идентификатор типа программы-отправителя сообщения
	pGenTrcMsg->senderType = EU_FP_PTPV;
	// идентификатор типа программы-получателя сообщения
	pGenTrcMsg->recipientType = EU_FP_ALL;
	// идентификатор экземпляра программы-отправителя сообщения
	pGenTrcMsg->senderInstance = 0;
	// идентификатор экземпляра программы-получателя сообщения
	pGenTrcMsg->recipientInstance = 0;
} // FormTrcMsgHdr()


const TMsgsForm::TGenTrcMsg TMsgsForm::TGenTrcMsg::CGenTrcMsg0;


} // namespace air

} // namespace PTPV
