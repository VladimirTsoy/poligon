#include <string.h>

#include "mathd.h"
#include "HSeaFAL.h"
#include "ESea.h"
#include "TSea.h"

namespace PTPV
{

namespace sea
{

struct TSea::TGenTrcMsg : public PTPV_TGenTrcMsg
{
	TGenTrcMsg() {}
	
	static const TGenTrcMsg CGenTrcMsg0;
}; // struct TGenTrcMsg

struct TSea::TMsgProc : public sea::TMsgProc
{
	TMsgProc() {}

	static const TMsgProc CMsgProc0;
}; // struct TMsgProc

struct TSea::TStateProc : public sea::TStateProc
{
	TStateProc() {}

	static const TStateProc CStateProc0;
}; // struct TStateProc


TSea::TSea(TZone monitoredZones[ZONE_MAX])
    : TrcProc(GeneralTrack), PrognProc(GeneralTrack),
      ZoneProc(GeneralTrack, monitoredZones), MsgsForm(GeneralTrack)
{
	Init();
	for ( int i = 1; i <= UGEN_SURFACE_TRC_MAX; i++ )
	{
		// чистка зоны обобщённых трасс			
		GeneralTrack[i] = CGenTrcS0;
	}
} // TSea()

TSea::~TSea() 
{
	int i;
	for ( i = 0; i <= SENS_MAX; i++ )
	{
		delete[] Link[i];
	}
} // ~TSea()

TSea::operator const TSea::TRes &() const
{
	return *pres;
}

// Приём сообщения о МО либо НО
int TSea::GetMsg(const TUTrcMsg &Msg, double T,
                 TMsgFormSet *pmsgFormSet, PTPV_TGenTrcMsg *pGenTrcMsg)
{
	int errors;
	if ( errors = MsgValidation(Msg, T) )
		// данные в сообщении некорректны
		/*MsgsForm(pmsgFormSet)*/;
	else
	{
		// Организация зоны информационных ситуаций обработки
		TMsgProc msgProc = TMsgProc::CMsgProc0;
		
		// Вызов местного диспетчера задач третичной обработки сообщений.
		TrcProc.MsgTaskChain(&Msg, &msgProc, Link);
		// Вызов местного диспетчера задач НУМ по сообщениям.
        dispatcherNUM.MsgTaskChain(Msg, &msgProc);
		// Вызов местн. диспетчера задач экстраполяции координат по сообщениям.
		PrognProc.MsgTaskChain(&msgProc);
		// Вызов местного диспетчера задач расчёта попадания объекта в зоны,
		// производимого по сообщениям.
		ZoneProc.MsgTaskChain(&msgProc);
		// Формирование результатов обработки сообщения потребителям.
		MsgsForm(T, &msgProc, pGenTrcMsg, pmsgFormSet);
	} // else

	return errors;
} // GetMsg()

// Корректировка статуса трассы
const TSea::TRes &TSea::TrcStateCheck(double currentT,
                                      fGiveResult *fpResult,
                                      void *pobject)
{
     unsigned int genTrcNum;
     int recordSize;
     /* int i=0; */
     TStateProc* pStateProc;

     //организация зоны для сообщения об обобщённой трассе
     PTPV_TGenTrcMsg GenTrcMsg;
     PTPV_TGenTrcMsg* pGenTrcMsg = &GenTrcMsg;

     //организация зоны информационных ситуаций обработки
     pStateProc=new TStateProc;
     recordSize=sizeof(TStateProc);
     for(genTrcNum=1;genTrcNum<=UGEN_SURFACE_TRC_MAX;genTrcNum++)
     {
       if(GeneralTrack[genTrcNum].genTrcT.busyState==EU_NO)// формуляр не занят
         continue;
       const bool stateTaskStart = (genTrcNum == 1);
       *pStateProc = TStateProc::CStateProc0;
       (*pStateProc).genTrcNum=genTrcNum;
       (*pStateProc).currentT=currentT;
       TrcProc.StateTaskChain(stateTaskStart, pStateProc,
                              Link, SensorDescription);
       // Вызов местного диспетчера задач период-ской экстраполяции координат.
       PrognProc.StateTaskChain(pStateProc);
       // Вызов местного диспетчера задач периодического расчёта попадания в
       // зоны объекта, описываемого трассой stateProc.genTrcNum.
		ZoneProc.StateTaskChain(pStateProc);
       
	   if ( pStateProc->genTrcDrop || pStateProc->sensTrcDrop )
       {
		 GenTrcMsg = TGenTrcMsg::CGenTrcMsg0;
		 (*pGenTrcMsg).trc = GeneralTrack[genTrcNum].genTrc;
         (*pGenTrcMsg).genTrcNum = genTrcNum;
         
		 if ( pStateProc->genTrcDrop )
         {
			pGenTrcMsg->trcState = EU_TS_END;
		 }
		 else
         {
			pGenTrcMsg->trcState = EU_TS_TRK;
		 }

		 if ( pStateProc->sensTrcDrop )
		 {
			pGenTrcMsg->sensDelete = EU_YES;
		 }
		 else
		 {
			pGenTrcMsg->sensDelete = EU_NO;
		 }
       
       // Рассылка выходного донесения.
       FormTrcMsgHdr(pGenTrcMsg, currentT);
       if ( fpResult != NULL )
		   fpResult(pGenTrcMsg, pobject);
 	   }
     }
     
     delete pStateProc;
     
     return *pres;
} // TrcStateCheck()

// Процедура приведения объекта к начальному состоянию.    
void TSea::Init()
{
	int recordSize;
	unsigned int i, j;
	// создание зоны характеристик источников
	recordSize=sizeof(TSensorDescription)*(SENS_MAX+1);
	memset(&SensorDescription,0,recordSize);
	
	// Заполнение характеристик источников по МО/НО
	// SensorDescription[i].type = 0; 
	SensorDescription[USENS_CP_MULTI].dataTemp = 30.;   
	SensorDescription[USENS_CP_MULTI].trackCount = 500;
	SensorDescription[USENS_CP_MULTI].maxTrackNumber = 500;
	
    SensorDescription[USENS_CP_A100].dataTemp = 30.;
	SensorDescription[USENS_CP_A100].trackCount = 500;
	SensorDescription[USENS_CP_A100].maxTrackNumber = 500;

	// формирование зоны связи трасс источников с обобщённой трассой
	for(i=0;i<=SENS_MAX;i++)
	{
		Link[i] =new TSensGenTrcLink[(SensorDescription[i].maxTrackNumber+1)];
		for(j=0;j<=SensorDescription[i].maxTrackNumber;j++)
		{
			// чистка зоны связи трасс источников с обобщённой трассой
			Link[i][j].genTrc=0;
			Link[i][j].identState=IS_NONE;
			Link[i][j].Data = NULL; // временно!!!
			Link[i][j].SeqSolution = NULL; // временно!!!

		}
 	}
	
	// обнуление счётчиков сообщений
	CountKeep.PTPV_Msg_Sea=0;

    dispatcherNUM.Init(SensorDescription, &GeneralTrack);
} // Init();

// Формирование заголовка PTPV_Msg_Sea
void TSea::FormTrcMsgHdr(PTPV_TGenTrcMsg* pGenTrcMsg,
						 double currentT)
{
     (*pGenTrcMsg).msgType=EU_MT_PTPV_SURFACE;                   // идентификатор типа сообщения
     (*pGenTrcMsg).msgLength=sizeof(PTPV_TGenTrcMsg);//длинапередаваемого сообщения
                                                     //в байтах, включая длину заголовка
     (*pGenTrcMsg).msgTime=currentT;                       // время отправки сообщения
     CountKeep.PTPV_Msg_Sea++;
     (*pGenTrcMsg).msgNum=CountKeep.PTPV_Msg_Sea;       //порядковый номер сообщения от 
                                                      // соответствующей программы-отправителя
     (*pGenTrcMsg).senderType=EU_FP_PTPV;            //идентификатор типа программы-отправителя сообщения 
     (*pGenTrcMsg).recipientType=EU_FP_ALL;         //идентификатор типа программы-получателя сообщения 
     (*pGenTrcMsg).senderInstance=0;        //идентификатор экземпляра программы-отправителя сообщения 
     (*pGenTrcMsg).recipientInstance=0;     //идентификатор экземпляра программы-получателя сообщения 
} // FormTrcMsgHdr()

// Формирование выходного донесения
void TSea::FormGenTrcMsg(int i, const TMsgProc* pMsgProc,
	                     PTPV_TGenTrcMsg* pGenTrcMsg)
{
    int recordSize;
    recordSize=sizeof(PTPV_TGenTrcMsg);   
    const int genTrcNum = pMsgProc->Update[i].trcNum;
    //организация зоны информационных ситуаций обработки
	pGenTrcMsg[i] = TGenTrcMsg::CGenTrcMsg0;
    (*(pGenTrcMsg+i)).genTrcNum = genTrcNum;
    if((*pMsgProc).Update[i].newTrc!=0)
	  (*(pGenTrcMsg+i)).trcState=EU_TS_NEW;
    else
      (*(pGenTrcMsg+i)).trcState=EU_TS_TRK;
    (*(pGenTrcMsg+i)).xyUpdate=(*pMsgProc).Update[i].xyUpdate;
    (*(pGenTrcMsg+i)).hUpdate=(*pMsgProc).Update[i].hUpdate;
    if((*pMsgProc).Update[i].sensAdd==EU_YES)
      (*(pGenTrcMsg+i)).sensAdd=EU_YES;
    else
      (*(pGenTrcMsg+i)).sensAdd=EU_NO;
    if((*pMsgProc).Update[i].sensDelete==EU_YES)
      (*(pGenTrcMsg+i)).sensDelete=EU_YES;
    else
      (*(pGenTrcMsg+i)).sensDelete=EU_NO;
    (*(pGenTrcMsg+i)).trc = GeneralTrack[genTrcNum].genTrc;
} // FormGenTrcMsg()


const TSea::TGenTrcMsg TSea::TGenTrcMsg::CGenTrcMsg0;

const TSea::TMsgProc TSea::TMsgProc::CMsgProc0;

const TSea::TStateProc TSea::TStateProc::CStateProc0;

} // namespace sea

} // namespace PTPV
