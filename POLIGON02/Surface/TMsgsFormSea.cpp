#include "TMsgsFormSea.h"

namespace PTPV
{

namespace sea
{

struct TMsgsForm::TGenTrcMsg : public PTPV_TGenTrcMsg
{
	TGenTrcMsg() {}

	static const TGenTrcMsg CGenTrcMsg0;
}; // struct TGenTrcMsg


TMsgsForm::TMsgsForm(TGeneralTrack &GeneralTrack)
         : Trc(GeneralTrack)
{} // TMsgsForm()

TMsgsForm::~TMsgsForm(void)
{}

// Формирование выходных сообщений по результатам обработки поступивших данных
void TMsgsForm::operator() (double T, const TMsgProc *pMsgProc,
	                        PTPV_TGenTrcMsg *pGenTrcMsg, TMsgFormSet *pmsgFormSet)
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

			pGenTrcMsg[i].hUpdate = pMsgProc->Update[i].hUpdate &&
			                        pMsgProc->Update[i].trcUpdate;
			if ( pMsgProc->Update[i].trcUpdate &&
			     pMsgProc->Update[i].xyUpdate )  // новое условие
			{ // произошло обновление координат

				pGenTrcMsg[i].xyUpdate = 1;
			} // if

			FormTrcMsgHdr(pGenTrcMsg + i, T);
		} // if genTrcChange
		pmsgFormSet->genTrcMsg[i] = genTrcChange;
		
	} // for (i) { pMsgProc->Update[i].trcNum }
} // FormGenTrcMsg()


// Формирование заголовка PTPV_Msg_Sea
void TMsgsForm::FormTrcMsgHdr(PTPV_TGenTrcMsg *pGenTrcMsg, double currentT)
{
	// идентификатор типа сообщения
	pGenTrcMsg->msgType = EU_MT_PTPV_SURFACE;
	// длина передаваемого сообщения в байтах, включая длину заголовка
	pGenTrcMsg->msgLength = sizeof(PTPV_TGenTrcMsg);
	// время отправки сообщения
	pGenTrcMsg->msgTime = currentT;
	// порядковый номер сообщения от соответствующей программы-отправителя
	CountKeep.PTPV_Msg_Sea++;
	pGenTrcMsg->msgNum = CountKeep.PTPV_Msg_Sea;
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


} // namespace sea

} // namespace PTPV
