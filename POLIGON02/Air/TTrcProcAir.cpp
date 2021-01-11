#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <iostream>

#include "mathd.h"
#include "TGeneralTrackAir.h"
#include "TTrcProcAir.h"

#include "OSLibFacilitiesAccomodation.h"

#if !(defined BORLAND)
using namespace std;
#endif

namespace PTPV
{
	
namespace air
{
using namespace androsor;

const TGenTrcS CGenTrcS0 = {{EU_NO}};

struct TTrcProc::TProcSituation
{
	// ситуации по входному сообщению
	unsigned char finish;                // конец работы по сообщению
	unsigned char newTrc;                // сообщение о новой трассе
	unsigned char oldTrc;                // сообщение о старой трассе
	unsigned char sequentialSolution;    // сообщение о трассе, находящейся
	                                     //_на последовательном анализе
	unsigned char sensTrcEnd;            // сброс трассы источника
	unsigned char conditionalIdent;      // coбщение отождествлено условно
	EMismatIdent  mismatIdent;           // несоответствие отождествления:
		                                    //_0 - соответствие
		                                    //_1 - несоотв-е по индив. номеру
		                                    //_2 - несоотв-е по XY и признакам
		                                    //_3 - несоотв-е по источн. сопров.
	/*u*/ int identSolution;             // номер отождествляемой трассы
	
	// отбор при отождествлении
	struct TAliveSelect
	{   // отбор по координатам "живых"
		/*u*/ int num;  // номер отобранной обобщённой трассы
		double dist;    // расстояние до отобранной обобщённой трассы
	} aliveSelect [ALIVE_SELEKT_MAX];
	unsigned int selectCount;
	
	struct TDeadSelect
	{   // отбор по координатам "мёртвых"
		/*u*/ int num;  // номер отобранной обобщённой трассы
		double dist;    // расстояние до отобранной обобщённой трассы
	} deadSelect;
	
	struct TIndNumbSelect
	{   // отбор по индивидуальному номеру
		unsigned int num;     // номер отобранной обобщённой трассы
		double dist;          // расстояние до отобранной обобщённой трассы
		char reTrc;           // замена старого решения
	} indNumbSelect;
		
	unsigned char error;    // ошибка при обработке сообщения
	
	// ситуации по обобщённой трассе
	struct TUpdate
	{
		/*u*/ int     trcNum;        // номер трассы в системе ТОИ
		unsigned char newTrc;        // признак новой обобщенной трассы
		unsigned char sensAdd;       // вписывание источника:
			                            // 1 - безусловное отождествление,
			                            // 2 - условное отождествление по ОГП,
			                            // 4 - условное отождествление по H,
			                            // 6 - условное отожд-ние по H и ОГП
		unsigned char sensDelete;    // вычёркивание источника 
		unsigned char updateTrc;     // обновление обобщённой трассы
		
		// обновление  признаков
		unsigned char xyUpdate;      // обновлениe X,Y
		unsigned char hUpdate;       // обновлениe H
		unsigned char OGPUpdate;     // обновлениe ОГП
		unsigned char OGPChange;     // изменение ОГП
		unsigned char SOSChange;     // изменениe бедствия
		unsigned char indNum;        // первый приход (вписывание) инд-го. ном.
	} Update[2];
		
	static const TProcSituation CSituation0;
}; // struct TProcSituation

	
	//===================================================
	TTrcProc::TTrcProc(TGeneralTrack &GeneralTrack, TSensGenTrcLink **pLink,
	                   TSensorDescription *pSensorDescription)
	                  : Link(pLink),
			            SensorDescription(pSensorDescription), Trc(GeneralTrack)
    {
	} // TTrcProc()

     //========================================
     //Диспетчер процесса обработки сообщений
     //=======================================
     void TTrcProc::MsgTaskChain(const TUTrcMsg &Msg, double T,
                                 TMsgProc* pMsgProc)
     {
     // инициализация и обнуление зоны ситуаций обработки 
     TProcSituation *pSituation;
     pSituation= new TProcSituation(TProcSituation::CSituation0);
     // диспетчеризация
     // анализ входного сообщения
     MsgCheck(Msg, T,
              pSituation,
              Link);
     if(((*pSituation).newTrc==1)||((*pSituation).sequentialSolution==1))
       {
       // отождествление
       Ident(Msg,pSituation,Link);
       }
     if((*pSituation).oldTrc==1)
       //Оценка соответствия первичного отождествления
       IdentCheck(Msg,
                  pSituation,
                  Link);
     if((*pSituation).mismatIdent==MI_IND_NUM)
       ReIdentIndNum(Msg,
                  pSituation,
                  Link);
     if((*pSituation).mismatIdent==MI_SENS)
       ReIdentSens(Msg,
                  pSituation,
                  Link);
     if((*pSituation).mismatIdent==MI_CRD)
       ReIdentCrd(Msg,
                  pSituation,
                  Link);
     if(((*pSituation).Update[0].sensAdd==1)||
        ((*pSituation).Update[0].sensDelete==1)||
        ((*pSituation).Update[0].newTrc==1)||
        ((*pSituation).Update[1].sensAdd==1)||
        ((*pSituation).Update[1].sensDelete==1)||
        ((*pSituation).Update[1].newTrc==1))
       //Реализация решения отождествления
       SolutionApply(Msg,
                     pSituation,
                     Link);
 	   if ( (pSituation->Update[0].updateTrc == 1 ||
	         pSituation->Update[1].updateTrc == 1)
			&& pSituation->sensTrcEnd != 1           )
				// обновление обобщённой трассы
				TrcUpdate(Msg,
						 /*pMsgProc,*/
						 pSituation,
						 Link);
	   //формирование выходного решения ТОИ 
       SolusionRecord(Msg,
                      pMsgProc,
                      pSituation,
                      Link);
     // освобождение зоны ситуаций обработки 
     delete pSituation;
     }


//============================================== 
// Анализ ситуации обработки
//===============================================
void TTrcProc::MsgCheck(const TUTrcMsg &Msg, double T,
                        TProcSituation *pSituation,
                        TSensGenTrcLink **pLink)
{
	if ( Msg.trcState == EU_TS_END )
	{
       if(pLink[Msg.sensNum][Msg.trcNum].genTrc==0)
         {    // а если не была заведена!!!
         // сброс трассы источника
         SensTrcEnd(Msg.sensNum,
                    Msg.trcNum,
                    pLink);
         // статус трассы источника - не отождествлена
         pLink[Msg.sensNum][Msg.trcNum].identState=IS_NONE;
         return;
         }
       (*pSituation).Update[0].trcNum=pLink[Msg.sensNum][Msg.trcNum].genTrc;
       (*pSituation).Update[0].sensDelete=1;
       (*pSituation).sensTrcEnd=1;
       (*pSituation).Update[0].updateTrc=1;
       }
     else
       {
         switch(pLink[Msg.sensNum][Msg.trcNum].identState)
         {
         case IS_NONE:
			if(Msg.xyUpdate==1)
             {
             SensTrcNew(Msg.sensNum,Msg.trcNum,pLink);
             (*pSituation).newTrc=1;
             break;
			 }
			return;
         case IS_SEQUENT_IDENT:
           if(Msg.xyUpdate==1)
             {
             (*pSituation).sequentialSolution=1;
             }
           break;
         default:
           (*pSituation).oldTrc=1;
           (*pSituation).Update[0].trcNum=pLink[Msg.sensNum][Msg.trcNum].genTrc;
         }
       }
     (*pLink[Msg.sensNum][Msg.trcNum].Data).tLastMsg=T;
     if(Msg.OGPUpdate==1)
       (*pLink[Msg.sensNum][Msg.trcNum].Data).OGP=Msg.OGP;
     (*pLink[Msg.sensNum][Msg.trcNum].Data).manevr=Msg.manevr;
     if(Msg.indNum!=0)
	   {
       (*pLink[Msg.sensNum][Msg.trcNum].Data).tIndNumUpdate=Msg.t;
	   (*pLink[Msg.sensNum][Msg.trcNum].Data).indNum=Msg.indNum;
	   }

     if(Msg.quantUpdate==1)
       // есть обновление количественного состава
       (*pLink[Msg.sensNum][Msg.trcNum].Data).quant=Msg.quant;

	 }

     //====================================================
     //Отождествление
     //====================================================
     void TTrcProc::Ident(const TUTrcMsg &Msg,
                           TProcSituation *pSituation,
                           TSensGenTrcLink **pLink)
       {
       //  отождествление по индивидуальному номеру 
       if(Msg.indNum!=0)
         {
         // есть инд. нoмер
         // Отбор по инд. номеру
         IndNumSelect(Msg,
                      pSituation,
                      pLink);
         if((*pSituation).indNumbSelect.num!=0)
           {
           // есть отобранные по индивидуальному номеру
           // вписывание источника в отобранную обобщённую трассу
           (*pSituation).Update[0].sensAdd=1;
           (*pSituation).Update[0].trcNum=(*pSituation).indNumbSelect.num;
           SeqentialSolutionDelete(Msg.sensNum,Msg.trcNum,pLink);
           if((*pSituation).indNumbSelect.reTrc!=0)
             // замена трассы источника в отобранной обобщённой трассе
             (*pSituation).Update[0].sensDelete=1;
           // произошло отождествление по индивидуальному номеру
           return;
           }
         }
       // отождествление по координатам 
       // отбор по координатам 
       CrdSelect(Msg,
                 pSituation);
       if((*pSituation).newTrc==1)
         {
         // трасса источника новая
         switch((*pSituation).selectCount)
           {
           // анализ списка отобранных трасс
           case 0:
             {
             // нет отобранных - формирование новой трассы
             (*pSituation).Update[0].newTrc=1;
             SeqentialSolutionDelete(Msg.sensNum,Msg.trcNum,pLink);
             //break;
			 return;
             }
           case 1:
             {
             // отобрана только одна трасса
             if((*pSituation).aliveSelect[0].dist<DIF_IDENT_XY)
               {
               //отобранная трасса в стробе отождествления - отождествление
               (*pSituation).Update[0].trcNum=(*pSituation).aliveSelect[0].num;
			   (*pSituation).Update[0].sensAdd=1;
               SeqentialSolutionDelete(Msg.sensNum,Msg.trcNum,pLink);
               //break;
			   return;
               }
             }
           default:
             {
			 // есть несколько отобранных Или отобранная не в стробе отождествления -
             // запись на последовательный анализ
             pLink[Msg.sensNum][Msg.trcNum].identState=IS_SEQUENT_IDENT;
             }
           }
         }
		 // трасса источника на последовательном анализе
		 switch(SeqIdent(Msg,pSituation,pLink))
         {
         case SI_NEW:
           {
           // формирование новой трассы
           (*pSituation).Update[0].newTrc=1;
           SeqentialSolutionDelete(Msg.sensNum,Msg.trcNum,pLink);
           break;
           }
         case SI_IDENT:
           {
           // отождествление
           (*pSituation).Update[0].sensAdd=1;
           (*pSituation).Update[0].trcNum=(*pSituation).identSolution;
           SeqentialSolutionDelete(Msg.sensNum,Msg.trcNum,pLink);
           break;
           }
         default:
           {
           pLink[Msg.sensNum][Msg.trcNum].identState=IS_SEQUENT_IDENT;
           }         
         }
       }

     
     //=================================================
     //Реализация отождествления
     //=================================================
     void TTrcProc::SolutionApply(const TUTrcMsg &Msg,
                                TProcSituation *pSituation,
                                TSensGenTrcLink **pLink)
      {
	unsigned int i;
	unsigned int genTrcNum;

      // цикл по шкале решений
	for(i=0;i<2;i++)
	  {
	  genTrcNum=(*pSituation).Update[i].trcNum;
	  if(genTrcNum!=0)
          {
	    if((*pSituation).Update[i].sensDelete==1)
            // вычёркивание трассы источника
            SensTrcDelete(Msg.sensNum,
                          Trc[genTrcNum].genTrc.sensTrcNum[Msg.sensNum],
						  0, pLink);
          if((*pSituation).sensTrcEnd==1)
            // сброс трассы источника
            SensTrcEnd(Msg.sensNum,
                            Msg.trcNum,
                            pLink);
	    if((*pSituation).Update[i].sensAdd!=0)
	      {
            // вписывание источника
            SensTrcAdd(genTrcNum,
                           Msg.sensNum,
                           Msg.trcNum, 0,
                           pLink);
	      (*pSituation).Update[i].updateTrc=1;
		  
		  // вписывание признаков условного отождествления
		  if((Msg.OGP==0)||( Trc[(*pSituation).Update[i].trcNum].genTrc.OGP==0))
		    {
		       if(Msg.hUpdate==0)  
			    // условное отождествление по ogp и h
				    pLink[Msg.sensNum][Msg.trcNum].identState=IS_CONDITION_OGP_H;
		      else
			    // условное отождествление по ogp
				    pLink[Msg.sensNum][Msg.trcNum].identState=IS_CONDITION_OGP;
	        }
	      else
		    if(Msg.hUpdate==0)  
		    // условное отождествление по h
			    pLink[Msg.sensNum][Msg.trcNum].identState=IS_CONDITION_H;
	      }
 	    if(Trc[genTrcNum].genTrc.sensCount==0)
	      {
            // перевод в "мертвые"
            // определение времени хранения трассы
	      Trc[genTrcNum].genTrcT.tHold=HoldTime(genTrcNum);
	      }
          }
        else
          {  
	    if((*pSituation).Update[i].newTrc==1)
	      {
            // формирование новой обобщённой трассы
            // поиск свободного места в gt_01
            genTrcNum=Trc.CreatRecord();
            if(genTrcNum!=0)
              {
              (*pSituation).Update[i].trcNum= genTrcNum;
              // чистка формуляра
              Trc[genTrcNum]=CGenTrcS0;
              // запись признака занятости формуляра
             Trc[genTrcNum].genTrcT.busyState=EU_YES;
              // вписывание источника
              SensTrcAdd(genTrcNum,
                            Msg.sensNum,
							Msg.trcNum, 0,
                            pLink);
              // запись признака обновления обобщённой трассы
              (*pSituation).Update[i].updateTrc=1;
	        }
            else // свободный формуляр не найден
			  { // окончание работы по данному решению:
			           // сброс трассы источника
			  SensTrcEnd(Msg.sensNum,
                        Msg.trcNum,
                        pLink);
			  // статус трассы источника - не отождествлена
			  pLink[Msg.sensNum][Msg.trcNum].identState=IS_NONE;
			  }
            }
          }
        }
      }

//=============================================
//формирование выходного решения ТОИ 
//=============================================
void TTrcProc::SolusionRecord(const TUTrcMsg &Msg,
                              TMsgProc* pMsgProc,
                              TProcSituation *pSituation,
                              TSensGenTrcLink **pLink)
{
	pMsgProc->error = pSituation->error;

	for ( int i = 0; i < 2; i++ )
	{
		pMsgProc->Update[i].trcNum = pSituation->Update[i].trcNum;
		if ( pSituation->Update[i].updateTrc == 1 )
		{
			pMsgProc->Update[i].newTrc = pSituation->Update[i].newTrc;
			pMsgProc->Update[i].trcUpdate = 1;
			pMsgProc->Update[i].sensAdd = pSituation->Update[i].sensAdd;
			pMsgProc->Update[i].sensDelete = pSituation->Update[i].sensDelete;
			pMsgProc->Update[i].OGPChange = pSituation->Update[i].OGPChange;
			pMsgProc->Update[i].xyUpdate = pSituation->Update[i].xyUpdate;
			pMsgProc->Update[i].hUpdate = pSituation->Update[i].hUpdate;
		}
	}
}

//---------------------------------------------------------------------------------------------------
//================================================
//Диспетчер периодического контроля статуса
//================================================
void TTrcProc::StateTaskChain(const bool, const double T,
                              TStateProc *pStateProc)
{
	StateCheck(T, pStateProc, Link, SensorDescription);
	if ( pStateProc->genTrcDrop == 1 )
		GenTrcEnd(pStateProc->genTrcNum);
}

      //=================================================
      //проверка статуса трассы
      //=================================================
      void TTrcProc::StateCheck(double T, TStateProc* pStateProc,
                                TSensGenTrcLink **pLink,
                                const TSensorDescription *sensorDescription)
      { 
      unsigned int sensNum;
      unsigned int trcNum;
      if(Trc[(*pStateProc).genTrcNum].genTrc.sensCount !=0)
        {
        for(sensNum=0;sensNum<SENS_MAX;sensNum++)
          {
          trcNum=Trc[(*pStateProc).genTrcNum].genTrc.sensTrcNum[sensNum];
          if(trcNum!=0)
            {
            // проверка сопровождения источника
            if ( T-pLink[sensNum][trcNum].Data->tLastMsg >
                 2. * sensorDescription[sensNum].dataTemp )
              {
              // источник не присылает донесений по данной трассе более ?? темпов поступления информации
              (*pStateProc).sensTrcDelete[sensNum]=trcNum;
			  (*pStateProc).sensTrcDrop = EU_YES;
			  SensTrcDelete(sensNum,
                                (*pStateProc).sensTrcDelete[sensNum], 0, pLink);
              // сброс трассы источника
              SensTrcEnd(sensNum,
                             (*pStateProc).sensTrcDelete[sensNum],
                             pLink);
              }
            }
          }
        if(Trc[(*pStateProc).genTrcNum].genTrc.sensCount==0)
	    {
          // перевод в "мертвые"
          // определение времени хранения трассы
	    Trc[(*pStateProc).genTrcNum].genTrcT.tHold=HoldTime((*pStateProc).genTrcNum);
	    }
        }
      if(Trc[(*pStateProc).genTrcNum].genTrc.sensCount==0)
        {
        if(Trc[(*pStateProc).genTrcNum].genTrcT.tHold<T)
          // истекло время хранения 
            (*pStateProc).genTrcDrop=1;
        }
      }


     //=============================================
     //Сброс обобщённой трассы
     //============================================
     void TTrcProc:: GenTrcEnd(unsigned int genTrcNum)
     {
     Trc.DestroyRecord(genTrcNum);
     Trc[genTrcNum].genTrcT.busyState = EU_NO;
     }

//--------------------------------------------------------------------------------------------

      //=================================================
      // организация новой трассы от источника
      // (отведение памяти под дополнительную информацию по трассе источника)
      //===============================================
      void TTrcProc::SensTrcNew(unsigned int sensNum,
                                  unsigned int trcNum,
                                  TSensGenTrcLink **pLink)
         {
         // запрос памяти для даных, присылаемых источником
         pLink[sensNum][trcNum].Data=new TSensTrcData;
         memset(pLink[sensNum][trcNum].Data,0,sizeof(TSensTrcData));
         
		 // запрос памяти для даных, используемых последовательным анализом
         pLink[sensNum][trcNum].SeqSolution=new TSeqSolution;
         memset(pLink[sensNum][trcNum].SeqSolution,0,sizeof(TSeqSolution));
         }

      //=============================================
      // сброс трассы источника
      // (освобождение памяти под дополнительную информацию по трассе источника)
      //===============================================
      void TTrcProc::SensTrcEnd(unsigned int sensNum,
                                   unsigned int trcNum,
                                   TSensGenTrcLink **pLink)
         {
         // освобождение памяти для данных, присылаемых источником
         delete pLink[sensNum][trcNum].Data;
         pLink[sensNum][trcNum].Data=NULL;
         // освобождение памяти для даных, используемых последовательным анализом
         delete pLink[sensNum][trcNum].SeqSolution;
         pLink[sensNum][trcNum].SeqSolution=NULL;
        }

      //=====================================================================
      // освобождение памяти для даных, используемых последовательным анализом
      //=====================================================================
      void TTrcProc::SeqentialSolutionDelete(unsigned int sensNum,
                                           unsigned int trcNum,
                                           TSensGenTrcLink **pLink)
        {
        delete pLink[sensNum][trcNum].SeqSolution;
        pLink[sensNum][trcNum].SeqSolution=NULL;
        }

      //===================================================
      // вписывание трассы источника в обобщённую трассу
      //=====================================================
      void TTrcProc::SensTrcAdd(unsigned int genTrcNum,
                                  unsigned int sensNum,
                                  unsigned int trcNum,
                                  unsigned char mobTrc,
                                  TSensGenTrcLink **pLink)
        {
        // статус трассы источника - отождествлена
        pLink[sensNum][trcNum].identState=IS_IDENT;
        // вписывание связки трассы источника с обобщённой трассой
        pLink[sensNum][trcNum].genTrc= genTrcNum;
        // вписывание источника соповождения в обобщённую трассу
        Trc[genTrcNum].genTrc.sensTrcNum[sensNum]=trcNum;
        Trc[genTrcNum].genTrc.sensCount ++ ;
		
		if ( mobTrc )
			// запись номера обобщённой трассы по носителю источника
			SensorDescription[sensNum].genTrcNum = genTrcNum;
        // освобождение памяти для даных, используемых последовательным анализом
        SeqentialSolutionDelete(sensNum,trcNum,pLink);
        }
 
     //=======================================================
     // вычёркивание трассы источника из обобщённой трассы
     //=======================================================
     void TTrcProc::SensTrcDelete(unsigned int sensNum,
                                  unsigned int trcNum,
                                  unsigned char mobTrc,
                                  TSensGenTrcLink **pLink)
        {
        // вычёркивание источника соповождения из обобщённой трассы
        Trc[pLink[sensNum][trcNum].genTrc].genTrc.sensTrcNum[sensNum]=0;
        Trc[pLink[sensNum][trcNum].genTrc].genTrc.sensCount --;
 		if ( mobTrc )
			// стирание номера обобщённой трассы по носителю источника
			SensorDescription[sensNum].genTrcNum = 0;
 		// вычёркивание связки трассы источника с обобщённой трассой
        pLink[sensNum][trcNum].genTrc=0;
        // статус трассы источника - не отождествлена
        pLink[sensNum][trcNum].identState=IS_NONE;
        }

      //=================================================
      // Определение времени хранения "мёртвой" трассы
      //=================================================
      double TTrcProc::HoldTime(unsigned int genTrcNum)
        {
        double holdTime;
        holdTime=Trc[genTrcNum].genTrc.tXYUpdate+DIF_DEAD_T;
        return holdTime;
        }

     //========================================
     // отбор обобщённых трасс по координатам
     //========================================
     void TTrcProc::CrdSelect(const TUTrcMsg &Msg,
                              TProcSituation *pSituation)
       {
       int genTrcNum;
       int selectNum;
       int selectCount;
       double difPsi;
       double difH;
       double difT;
       double dist;
       double distIn;
       double distOut;
       int numOut;
       int numIn;
       struct
         {
         double x;
         double y;
         } difCrd;
       selectCount=0;
       for(genTrcNum=1;genTrcNum<=UGEN_TRC_MAX;genTrcNum++)
         {
         //  анализ признака занятости формуляра 
         if(Trc[genTrcNum].genTrcT.busyState==EU_NO)
           continue;
		 //  анализ признакoв тренажа на равенствo 
         if(Msg.imitObj!=Trc[genTrcNum].genTrc.imitObj)
           continue;
         //  анализ инд. нoмерoв 
		 /*if((Msg.reqLine==BIUS_A100::PTPV::EReqLine::REQ_LINE_PASSWORD)||
            (Msg.reqLine==BIUS_A100::PTPV::EReqLine::REQ_LINE_RAINBOW))
		 */
           {
           if((Msg.indNum!=0)&&(Trc[genTrcNum].genTrc.indNum!=0))
               continue;
           }
         //  анализ признакoв OGP на непротиворечивсть 
		 if((Msg.OGP!=EU_OGP_UNKNOWN)&&(Trc[genTrcNum].genTrc.OGP!=EU_OGP_UNKNOWN))
           { 
           if(Msg.OGP!=Trc[genTrcNum].genTrc.OGP)
             {
             if((Msg.OGP==EU_OGP_HOSTILE)||(Trc[genTrcNum].genTrc.OGP==EU_OGP_HOSTILE))
               continue;
             }
           }
	   if(Trc[genTrcNum].genTrc.sensCount==0)
           {
           // обобщенная трасса "мертвая"
           // анализ курсoв трасс,
           difPsi=Trc[genTrcNum].genTrc.psi-Msg.psi;
	     if(difPsi<0)
             difPsi= -difPsi;
           if(difPsi>DIF_DEAD_PSI)
             continue;
           }
/*         // анализ источника сопровождения
         if(Trc[genTrcNum].genTrc.sensTrcNum [Msg.sensNum]!=0)
           continue;
*/
         if(((*pSituation).mismatIdent==MI_SENS)||((*pSituation).Update[0].trcNum!=genTrcNum))
           {
           // трасса на первичном отождествлении или на переотождествлении
           // но отбирает не саму себя
           // анализ источника сопровождения
           if(Trc[genTrcNum].genTrc.sensTrcNum [Msg.sensNum]!=0)
             continue;
           }

         // анализ высот
         if(Msg.hUpdate==1)
           {
           // в пришедшем сообщении обновлена высота 
           difH=Trc[genTrcNum].genTrc.h-Msg.h;
	     if(difH<0)
             difH= -difH;
           if(difH>DIF_H)
             continue;
           }
         // анализ координат
         difT=Msg.t-Trc[genTrcNum].genTrc.tXYUpdate;
         // экстраполяция и проверка по стробу координаты x
         difCrd.x=fabs(Trc[genTrcNum].genTrc.x+Trc[genTrcNum].genTrc.vX*difT-Msg.x);
         if((difCrd.x)>DIF_XY)
           continue;
         // экстраполяцияи проверка по стробу координаты y
         difCrd.y=fabs(Trc[genTrcNum].genTrc.y+Trc[genTrcNum].genTrc.vY*difT-Msg.y);
         if((difCrd.y)>DIF_XY)
           continue;
         // вычисление расстояния
         dist=sqrt(difCrd.x*difCrd.x+difCrd.y*difCrd.y);
         // запись обобщенной трассы в буфер "живых" трасс
         // с упорядочиванием по возрастанию расстояний 
         distIn=dist;
         numIn=genTrcNum;
         for(selectNum=0;selectNum<ALIVE_SELEKT_MAX;selectNum++)
           {
           if((*pSituation).aliveSelect[selectNum].num!=0)
             {
             if(distIn>=(*pSituation).aliveSelect[selectNum].dist)
               continue;
             distOut=(*pSituation).aliveSelect[selectNum].dist;
             numOut=(*pSituation).aliveSelect[selectNum].num;
             (*pSituation).aliveSelect[selectNum].dist=distIn;
             (*pSituation).aliveSelect[selectNum].num=numIn;
             distIn=distOut;
             numIn=numOut;
             }
           else
             {
             (*pSituation).aliveSelect[selectNum].dist=distIn;
             (*pSituation).aliveSelect[selectNum].num=numIn;
             break;
             }
           //  увеличение счетчика отобранных обобщенных трасс 
           }
         if(selectCount<ALIVE_SELEKT_MAX)
           selectCount=selectCount+1;
         }
       (*pSituation).selectCount=selectCount;
       }

     //====================================================
     // отбор обобщённых трасс по индивидуальному номеру
     //====================================================
     void TTrcProc::IndNumSelect(const TUTrcMsg &Msg,
                                 TProcSituation *pSituation,
                                 TSensGenTrcLink **pLink)
       {
       int genTrcNum;
       char reTrc;
       int sensTrcNum;
       int selectCount;
       double difT;
       double dist;
       struct
         {
         double x;
         double y;
         } difCrd;
       if(Msg.indNum==0)
		   return;
	   selectCount=0;
       for(genTrcNum=1;genTrcNum<=UGEN_TRC_MAX;genTrcNum++)
         {
         //  анализ признака занятости формуляра 
         if(Trc[genTrcNum].genTrcT.busyState==EU_NO)
           continue;
         //  анализ признакoв тренажа на равенствo 
         if(Msg.imitObj!=Trc[genTrcNum].genTrc.imitObj)
           continue;
         //  анализ линии запроса инд. нoмерoв 
		 /*if((Msg.reqLine==BIUS_A100::PTPV::EReqLine::REQ_LINE_PASSWORD)||
			 (Msg.reqLine==BIUS_A100::PTPV::EReqLine::REQ_LINE_RAINBOW))
		 */
           {
           //  отбор по номеру "ПАРОЛЬ"
           /*if(Trc[genTrcNum].genTrc.indNum!=0)*/
             {
             // во входном донесении и в обобщённой трассе
             // есть инд. номер "ПАРОЛЬ"
             if(Msg.indNum!=Trc[genTrcNum].genTrc.indNum)
               // номера различны - нет отождествления
               continue;
             reTrc=0;
             // анализ источника сопровождения
             sensTrcNum=Trc[genTrcNum].genTrc.sensTrcNum[Msg.sensNum];
             if(sensTrcNum!=0)
               {
               // источник сопровождает отбираемую трассу
               if((Msg.t-(*pLink[Msg.sensNum][sensTrcNum].Data).tIndNumUpdate)<
                                                            DIF_IND_NUM_T)
                 {
                 // данный источник сопровождает отбираемую трассу по 
                 // индивидуальному номеру - нет отождествления
                 continue;
                 }
               // данный источник сопровождает отбираемую трассу но 
               // индивидуальный номер приходил давно - замена старого решения,
               // отождествление
               reTrc=1;
               }
 
			   // анализ координат
               difT=Msg.t-Trc[genTrcNum].genTrc.tXYUpdate;
               // экстраполяция координаты x
               difCrd.x=fabs(Trc[genTrcNum].genTrc.x+Trc[genTrcNum].genTrc.vX*difT-Msg.x);
               // экстраполяция координаты y
               difCrd.y=fabs(Trc[genTrcNum].genTrc.y+Trc[genTrcNum].genTrc.vY*difT-Msg.y);
               // вычисление расстояния
               dist=sqrt(difCrd.x*difCrd.x+difCrd.y*difCrd.y);
               if(dist>DIF_IND_NUM_XY)
                 continue;
               if((dist<(*pSituation).indNumbSelect.dist)||(selectCount==0))
                 {
                 selectCount=1;
                 (*pSituation).indNumbSelect.dist=dist;
                 (*pSituation).indNumbSelect.num=genTrcNum;
                 (*pSituation).indNumbSelect.reTrc=reTrc;
                 }
             }
           }
         }
       }

     //=================================
     // контроль Отождествления
     //=================================
     void TTrcProc::IdentCheck(const TUTrcMsg &Msg,
                               TProcSituation *pSituation,
                               TSensGenTrcLink **pLink)
         {
       int genTrcNum;
       // int sensTrcNum;
       // int i;
       double difT;
       double difH;
       double dist;
       struct
         {
         double x;
         double y;
         } difCrd;
       // int quant;

         genTrcNum=(*pSituation).Update[0].trcNum;
         //проверка обновления по xy
         if(Msg.xyUpdate==0)
           {
           // обновления координат нет - нет возможности переотождествления
           (*pSituation).Update[0].updateTrc=1;
           return;
           }
         // анализ индивидуального номера
/*         //  анализ линии запроса инд. нoмерoв 
         if((Msg.reqLine==REQ_LINE_PASSWORD)||
            (Msg.reqLine==REQ_LINE_RAINBOW))
           {
             //  анализ по номеру "ПАРОЛЬ"
           if(Trc[genTrcNum].genTrc.indNum!=0)
             {
             // во входном донесении и в обобщённой трассе
             // есть инд. номер "ПАРОЛЬ"
             if(Msg.indNum!=Trc[genTrcNum].genTrc.indNum)
               {
               // номера различны
               quant=0;
               for(i=1;i<SENS_MAX;i++)
                 {
                 sensTrcNum=Trc[genTrcNum].genTrc.sensTrcNum[i];
                 if(sensTrcNum==0)
                   continue;
                 if((Msg.t-(*pLink[i][sensTrcNum].Data).tIndNumUpdate)<
                                                            DIF_IND_NUM_T)
                   // подсчёт количества источников сопровождающих обобщённую
                   // трассу по индивидуальному номеру
                   quant++;
                 }
               if(((quant==1)&&(Trc[genTrcNum].genTrc.sensTrcNum[9]==0))||
                  (quant>1))
                 {
                 // несоответствие по инд. номеру
                 (*pSituation).mismatIdent=MI_IND_NUM;
                 return;
                 }
               }
             }
*/
         if(Msg.indNum!=0)
		   {
		   if(Msg.indNum!=Trc[genTrcNum].genTrc.indNum) 
             {
             // несоответствие по инд. номеру "пароль"
             (*pSituation).mismatIdent=MI_IND_NUM;
             return;
             }
           }
         // источник сопровождения один
         if(Trc[genTrcNum].genTrc.sensCount==1)
           {
           Trc[genTrcNum].genTrcT.mismatSensCount++;
           if(Trc[genTrcNum].genTrcT.mismatSensCount>=MISMAT_SENS_COUNT)
             {
				 if(Msg.OGP!=EU_OGP_UNKNOWN)
               {
               // трасса определена по ОГП
               // несоответствие по количеству источников
               Trc[genTrcNum].genTrcT.mismatSensCount=0;
               (*pSituation).mismatIdent=MI_SENS ;
               return;
               }
             Trc[genTrcNum].genTrcT.mismatSensCount=0;
             }
           // несоответствия нет обновление
           (*pSituation).Update[0].updateTrc=1;
           return;
           }
         // анализ признака тренажа
         if(Msg.imitObj!=Trc[genTrcNum].genTrc.imitObj)
           {
           // сообщение не соответствует обобщенной трассе по
           // признаку тренажа
           (*pSituation).mismatIdent=MI_CRD;
           (*pLink[Msg.sensNum][Msg.trcNum].Data).mismatXYCount=0;
           return;
           }
         // проверка условного отождествления по ОГП
         if ((pLink[Msg.sensNum][Msg.trcNum].identState==IS_CONDITION_OGP)||
             (pLink[Msg.sensNum][Msg.trcNum].identState==IS_CONDITION_OGP_H))
           {
           if (Msg.OGPUpdate==1) 
             {
             // есть измерение  ОГП
             // стирание условного отождествления по ОГП
             if (pLink[Msg.sensNum][Msg.trcNum].identState==IS_CONDITION_OGP)
               pLink[Msg.sensNum][Msg.trcNum].identState=IS_IDENT;
             else
               pLink[Msg.sensNum][Msg.trcNum].identState=IS_CONDITION_H;
             if(Msg.OGP!=Trc[genTrcNum].genTrc.OGP) 
               {
               if ((Msg.OGP==1)||(Trc[genTrcNum].genTrc.OGP==1))
                 {
                 // если ОГП = 1 
                 // сообщение не соответствует обобщенной трассе по ОГП
                 // Выход на переотождествление по XY
                 (*pSituation).mismatIdent=MI_CRD;
                 (*pLink[Msg.sensNum][Msg.trcNum].Data).mismatXYCount=0;
                 return;
                 }
               }
             }
           }
         // проверка условного отождествления по высоте
         if ((pLink[Msg.sensNum][Msg.trcNum].identState==IS_CONDITION_H)||
             (pLink[Msg.sensNum][Msg.trcNum].identState==IS_CONDITION_OGP_H))
           {
           if (Msg.hUpdate==1) 
             {
             // в пришедшем сообщении обновлена высота 
             // стирание условного отождествления по высоте
             if (pLink[Msg.sensNum][Msg.trcNum].identState==IS_CONDITION_H)
               pLink[Msg.sensNum][Msg.trcNum].identState=IS_IDENT;
             else
               pLink[Msg.sensNum][Msg.trcNum].identState=IS_CONDITION_OGP;           
             difH=Trc[genTrcNum].genTrc.h-Msg.h;
  	       if(difH<0)
               difH= -difH;
             if(difH>DIF_H)
               {
               // сообщение не соответствует обобщенной трассе по высоте
               // Выход на переотождествление по XY
               (*pSituation).mismatIdent=MI_CRD;
               (*pLink[Msg.sensNum][Msg.trcNum].Data).mismatXYCount=0;
               return;
               }
             }  
           }
         // анализ координат
         difT=Msg.t-Trc[genTrcNum].genTrc.tXYUpdate;
         // экстраполяция координаты x
         difCrd.x=fabs(Trc[genTrcNum].genTrc.x+Trc[genTrcNum].genTrc.vX*difT-Msg.x);
         // экстраполяция координаты y
         difCrd.y=fabs(Trc[genTrcNum].genTrc.y+Trc[genTrcNum].genTrc.vY*difT-Msg.y);
         // вычисление расстояния
         dist=sqrt(difCrd.x*difCrd.x+difCrd.y*difCrd.y);
         if(dist<DIF_CHECK_XY)
           {
           // сообщение соответствует обобщенной трассе по  XY
           (*pSituation).Update[0].updateTrc=1;
           (*pLink[Msg.sensNum][Msg.trcNum].Data).mismatXYCount=0;
           return;
           }
         (*pLink[Msg.sensNum][Msg.trcNum].Data).mismatXYCount++;
         if((*pLink[Msg.sensNum][Msg.trcNum].Data).mismatXYCount
            <MISMAT_XY_COUNT)
           {
           // решение о соответствии сообщения обобщенной трассе
           // по XY не принимается
           (*pSituation).Update[0].updateTrc=1;
           return;
           }
         // сообщение не соответствует обобщенной трассе по  XY
         // Выход на переотождествление по XY
         (*pSituation).mismatIdent=MI_CRD;
         (*pLink[Msg.sensNum][Msg.trcNum].Data).mismatXYCount=0;
         return;
         }

     //==============================================
     // переотождествление по индивидуальному номеру
     //===============================================
     void TTrcProc::ReIdentIndNum(const TUTrcMsg &Msg,
                                  TProcSituation *pSituation,
                                  TSensGenTrcLink **pLink)
       {
       // Отбор по инд. номеру
       IndNumSelect(Msg,
                    pSituation,
                    pLink);
       if((*pSituation).indNumbSelect.num!=0)
         {
         // есть отобранные по индивидуальному номеру
         // вычёркивание источника из старой обобщённой трассы
         (*pSituation).Update[0].sensDelete=1;
         // вписывание источника в отобранную обобщённую трассу
         (*pSituation).Update[1].sensAdd=1;
         (*pSituation).Update[1].trcNum=(*pSituation).indNumbSelect.num;
         SeqentialSolutionDelete(Msg.sensNum,Msg.trcNum,pLink);
         if((*pSituation).indNumbSelect.reTrc!=0)
           // замена трассы источника в отобранной обобщённой трассе
           (*pSituation).Update[1].sensDelete=1;
         // произошло отождествление по индивидуальному номеру
         return;
         }
       // нет отобранных 
       if(Trc[(*pSituation).Update[0].trcNum].genTrc.indNum==0)
         {
         // ранее инд. номер обобщённой трассы был == 0
         // - сохранение старого решения
         (*pSituation).Update[0].updateTrc=1;
          return;
         }
       // вычёркивание источника из старой обобщённой трассы
       (*pSituation).Update[0].sensDelete=1;
       // формирование новой трассы
       (*pSituation).Update[1].newTrc=1;
       SeqentialSolutionDelete(Msg.sensNum,Msg.trcNum,pLink);
       }

     //======================================
     // переотождествление по координатам 
     //======================================
     void TTrcProc::ReIdentCrd(const TUTrcMsg &Msg,
                                  TProcSituation *pSituation,
                                  TSensGenTrcLink **pLink)
       {
       // отбор по координатам 
       CrdSelect(Msg,
                 pSituation);
       if((*pSituation).selectCount!=0)
         {
         // есть отобраные трассы
         if((*pSituation).aliveSelect[0].dist<DIF_IDENT_XY)
           {
		     if((*pSituation).aliveSelect[0].num==(*pSituation).Update[0].trcNum)
			   {
			   // сохранение старого решения
			   (*pSituation).Update[0].updateTrc=1;
			   return;
			   }
			   //отобранная трасса в стробе отождествления - отождествление
           // вычёркивание источника из старой обобщённой трассы
           (*pSituation).Update[0].sensDelete=1;
           // вписывание источника в отобранную обобщённую трассу
           (*pSituation).Update[1].sensAdd=1;
           (*pSituation).Update[1].trcNum=(*pSituation).aliveSelect[0].num;
           SeqentialSolutionDelete(Msg.sensNum,Msg.trcNum,pLink);
           // произошло отождествление по координатам
           return;
           }
         }
// ??? ввести отождествление с мёртвыми и сравнение со старым решением       
       // нет отобранных, в стробе отождествления трасс
       // вычёркивание источника из старой обобщённой трассы
       (*pSituation).Update[0].sensDelete=1;
       // формирование новой трассы
       (*pSituation).Update[1].newTrc=1;
       SeqentialSolutionDelete(Msg.sensNum,Msg.trcNum,pLink);
       }
 
     //========================================
     // переотождествление по источнику
     //======================================
     void TTrcProc::ReIdentSens(const TUTrcMsg &Msg,
                                TProcSituation *pSituation,
                                TSensGenTrcLink **pLink)
       {
       // отбор по координатам 
       CrdSelect(Msg,
                 pSituation);
       if((*pSituation).selectCount!=0)
         {
		 // есть отобраные трассы
         if((*pSituation).aliveSelect[0].dist<DIF_IDENT_XY)
           {
           //отобранная трасса в стробе отождествления - отождествление
           if((Trc[(*pSituation).aliveSelect[0].num].genTrc.sensCount==1))
             {
		     if(Trc[(*pSituation).aliveSelect[0].num].genTrc.tStart>
			    Trc[(*pSituation).Update[0].trcNum].genTrc.tStart)
			   {
			   // отобранная трасса сопровождается одном источником и старше
			   // отождествляемой - сохранение старого решения
			   (*pSituation).Update[0].updateTrc=1;
			   return;
			   }
		     }
           // отождествление с отобранной трассой
           // вычёркивание источника из старой обобщённой трассы
           (*pSituation).Update[0].sensDelete=1;
           // вписывание источника в отобранную обобщённую трассу
           (*pSituation).Update[1].sensAdd=1;
           (*pSituation).Update[1].trcNum=(*pSituation).aliveSelect[0].num;
           SeqentialSolutionDelete(Msg.sensNum,Msg.trcNum,pLink);
           // произошло отождествление по координатам
           return;
           }
         }
       // нет отобранных, в стробе отождествления трасс
             // отождествляемой - сохранение старого решения
             (*pSituation).Update[0].updateTrc=1;
       }

      //--------------------------------------------------
      // Процедура последовательного анализа
      //--------------------------------------------------
      ESeqIdent TTrcProc:: SeqIdent(const TUTrcMsg &Msg,
                                    TProcSituation *pSituation,
                                    TSensGenTrcLink **pLink)
      {
      // макрокоманда вычисления функции принадлежности по расстоянию
      #define Fuzzy(dist) (1/(1+FUZZY_KOEF*dist*dist))
      double  fuzzy;   // значение функции принадлежности
      double  crit;    // значение критерия
      unsigned int sensNum;       // номер источника
      unsigned int trcNum;        // номер трассы источника
      unsigned int identSolution; // решение последовательного анализа
      /* unsigned */ int selectTrcQuant;  // количество отобранных объектов
      /* unsigned */ int selectNum;     // номер объекта в списке отобранных
      /* unsigned */ int candidateNum; // номер объекта в списке кандидатов на отождествление 
      unsigned int newCandidateNum;  // номер нового объекта в списке кандидатов на отождествление
      sensNum=Msg.sensNum;
      trcNum=Msg.trcNum;
      selectTrcQuant=(*pSituation).selectCount;
      if((*pLink[sensNum][trcNum].SeqSolution).step==0)
        {
        // первый шаг последовательного анализа
        //  начальное заполнение формуляра SelectTrc
        (*pLink[sensNum][trcNum].SeqSolution).step=1;
        (*pLink[sensNum][trcNum].SeqSolution).selectTrcQuant=selectTrcQuant;
        // запись отобранных обобщённых трасс
        for(candidateNum=0;candidateNum<selectTrcQuant;candidateNum++)
          {
	     (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].genTrcNum=
                                        (*pSituation).aliveSelect[candidateNum].num;
          // вычисление функции принадлежности
          fuzzy=Fuzzy((*pSituation).aliveSelect[candidateNum].dist);
          // построение вариационного ряда на первом шаге анализа
          (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMinExtreme=fuzzy;
          (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMin=fuzzy; 
          (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMaxExtreme=fuzzy;
          (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMax=fuzzy;
          }
        }
      else
        {
  	    unsigned char mask[ALIVE_SELEKT_MAX]
		                  = {0}; // маска объектов в списке отобранных
                                 // имеющихся в списке кандидатов
        //  пoвтoрный выхoд на пoсл. анализ
        (*pLink[sensNum][trcNum].SeqSolution).step++;
        // цикл по списку кандидатов последовательного анализа и его корректировка
        for(candidateNum=0;candidateNum<SEQ_CANDIDATE_MAX;candidateNum++)
          {
          if((*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].genTrcNum==0)
            // пустой формуляр
            continue;
          // цикл по списку отобранных на текущем шаге анализа
          for(selectNum=0;selectNum<selectTrcQuant;selectNum++)
            {
            if((*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].genTrcNum==
                                       (*pSituation).aliveSelect[selectNum].num)
              {
              // в списке отобранных на отождествление найден
              // рассматриваемый кандидат (candidateNum) - корректировка вариационного ряда 
              mask[selectNum]=1;
              // вычисление функции принадлежности
              fuzzy=Fuzzy((*pSituation).aliveSelect[selectNum].dist);
              // построение вариационного ряда на n-ном шаге анализа
              if(fuzzy<(*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMinExtreme)           
                {
                // значение принадлежности меньше самого минимального
                (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMin=
                   (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMinExtreme;
                (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMinExtreme=fuzzy;
                }  
              else 
                { 
                // значение принадлежности меньше минимального
                if(fuzzy<(*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMin)
                  (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMin=fuzzy;
                else 
                  {
                  if(fuzzy>(*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMaxExtreme)
                    {
                    // значение принадлежности больше самого максимального
                    (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMax=
                    (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMaxExtreme;
	              (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMaxExtreme=fuzzy;
	              } 
                  else 
	              if(fuzzy>(*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMax)
                      // значение принадлежности больше  максимального
                      (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMax=fuzzy;
                  } 
                }
              // корректировка вариационного ряда завершена
              break;
              }
            }
          if(selectNum==selectTrcQuant)
          
          // 
            {
            // просмотрен весь список отобранных на текущем шаге отождествления и в нем нет
            // рассматриваемого кандидата (candidateNum) - вычёркивание кандидата 
            (*pLink[sensNum][trcNum].SeqSolution).selectTrcQuant--;
            (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].genTrcNum=0;
            (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMinExtreme=0;
            (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMin=0; 
            (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMaxExtreme=0;
            (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMax=0;
            }
          }
        for(selectNum=0;selectNum<selectTrcQuant;selectNum++)
           {
           if(mask[selectNum]==0)
             {
             //данный отобранный не являлся кандидатом на отождествление -
             // вписывание нового кандидата на отождествление
             // поиск свободного места 
             for(newCandidateNum=0;newCandidateNum<SEQ_CANDIDATE_MAX;newCandidateNum++)
               {
               if((*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[newCandidateNum].genTrcNum==0)
                 break;
               }
             if(newCandidateNum<SEQ_CANDIDATE_MAX)
               {
               // есть свободное место
               (*pLink[sensNum][trcNum].SeqSolution).selectTrcQuant++;
               (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[newCandidateNum].genTrcNum=
                                        (*pSituation).aliveSelect[selectNum].num;
               // вычисление функции принадлежности
               fuzzy=Fuzzy((*pSituation).aliveSelect[selectNum].dist);
               // построение вариационного ряда при вписывании нового кандидата
               (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[newCandidateNum].fuzzyMinExtreme=fuzzy;
	         (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[newCandidateNum].fuzzyMin=fuzzy; 
	         (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[newCandidateNum].fuzzyMaxExtreme=fuzzy;
	         (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[newCandidateNum].fuzzyMax=fuzzy;
               }
             }
           }
         }
       // вынесение решения
       // 
       if((*pLink[sensNum][trcNum].SeqSolution).selectTrcQuant==0)
         {
         // нет кандидатов на отождествление 
         // запись решения об образовании новой обобщённой трассы
	    (*pLink[sensNum][trcNum].SeqSolution).step=0;
	    return(SI_NEW);
	    }
        for(candidateNum=0;candidateNum<SEQ_CANDIDATE_MAX;candidateNum++)
          {
          if((*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].genTrcNum==0)
            // пустой формуляр
            continue;
          // вычисление критерия по сформированному вариационному ряду
          (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].crit= 
             (1.-(*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMax)/
	       (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].fuzzyMin;
          }
      // поиск min критерия
      crit=CRIT_MAX+1.;
      // Цикл по списку последнего анализа
      for(candidateNum=0;candidateNum<SEQ_CANDIDATE_MAX;candidateNum++)
        if( (*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].genTrcNum!=0 &&
			(*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].crit<crit )
          {
          crit=(*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].crit;
          identSolution=(*pLink[sensNum][trcNum].SeqSolution).CandidateTrc[candidateNum].genTrcNum;
          }
      //  проверка на шаге LIMIT_STEP_MIN
      if((*pLink[sensNum][trcNum].SeqSolution).step>=LIMIT_STEP_MIN)
        {
        //  сравнение критерия c пороговыми значениями
        if(crit<CRIT_MIN)
          {
          (*pLink[sensNum][trcNum].SeqSolution).step=0;
          (*pSituation).identSolution=identSolution;
          return(SI_IDENT);
          }
        if(crit>CRIT_MAX)
          {
          (*pLink[sensNum][trcNum].SeqSolution).step=0;
          return(SI_NEW);
          }
        }
      // проверка на шаге LIMIT_STEP_MAX
      if((*pLink[sensNum][trcNum].SeqSolution).step>=LIMIT_STEP_MAX)
        {
        (*pLink[sensNum][trcNum].SeqSolution).step=0;
        //  сравнение критерия c пороговыми значениями
        if(crit<CRIT)
          {
          // запись решения об отождествлении с отобранной обобщённой трассой
          (*pSituation).identSolution=identSolution;
          return(SI_IDENT);
          }
        // запись решения об образовании новой обобщённой трассы
        return(SI_NEW);
        }
      // запись решения о продолжении последовательного анализа
      return(SI_WAIT);
      }

     //========================================
     // обновление координат заменой
     //========================================
     void TTrcProc::ChangeUpdate(const TUTrcMsg &Msg,
                                 TProcSituation * /*pSituation*/,
                                 unsigned int genTrcNum)
     {
     // есть обновление координат
     Trc[genTrcNum].genTrc.tXYUpdate=Msg.t;
     Trc[genTrcNum].genTrc.x=Msg.x;
     Trc[genTrcNum].genTrc.y=Msg.y;
     Trc[genTrcNum].genTrc.v=Msg.v;
     Trc[genTrcNum].genTrc.psi=Msg.psi;
     Trc[genTrcNum].genTrc.vX=Msg.vX;
     Trc[genTrcNum].genTrc.vY=Msg.vY;
     Trc[genTrcNum].genTrc.trustXY=Msg.trustXY;
	 }

	 //========================================
     // обновление координат фильтрацией
     //========================================
     void TTrcProc::FilterUpdate(const TUTrcMsg &Msg,
                                 TProcSituation * /*pSituation*/,
                                 TSensGenTrcLink **pLink,
                                 unsigned int genTrcNum)
     {
     double filterXY;
     double filterV;
     double difFilter;
     double difT;
     // double difH;
     // double dist;
     int signX;
     int signY;
     struct
       {
       double x;
       double extrX;
       double y;
       double extrY;
       } difCrd;
     // выбор коэффициентов сглаживания
     if(Trc[genTrcNum].genTrc.manevr==EU_YES)
	 {
       // коэффициенты сглаживания пpи маневpе
	 filterXY=FILTER_M_XY; 
	 filterV=FILTER_M_V;
	 difFilter=DIF_M_FILTER_XY;
	 }
     else
	 {
       // коэффициенты сглаживания без маневpа
	 filterXY=FILTER_XY;  
	 filterV=FILTER_V;
	 difFilter=DIF_FILTER_XY;
	 }
     signX=0;
     signY=0;
     difT=Msg.t-Trc[genTrcNum].genTrc.tXYUpdate;
     Trc[genTrcNum].genTrc.tXYUpdate=Msg.t;
     // экстраполяция координаты x
     difCrd.extrX=Trc[genTrcNum].genTrc.x+Trc[genTrcNum].genTrc.vX*difT;
     difCrd.x=Msg.x-difCrd.extrX;
     // экстраполяция координаты y
     difCrd.extrY=Trc[genTrcNum].genTrc.y+Trc[genTrcNum].genTrc.vY*difT;
     difCrd.y=Msg.y-difCrd.extrY;

     // анализ на попадание в стpоб сопровождения
     if(difCrd.x>difFilter)
	 signX=1;
     if(difCrd.x<(-difFilter))
	 signX=-1;
     if(difCrd.y>difFilter)
	 signY=1;
     if(difCrd.y<(-difFilter))
	 signY=-1;

     // обработка при попадании в строб сопровождения
     if((signX==0)&&(signY==0))
	 {
       // 0--> счетчик необновлений
	 (*pLink[Msg.sensNum][Msg.trcNum].Data).mismatXYCount=0;
	 Trc[genTrcNum].genTrc.x=static_cast<float>(
		 difCrd.extrX+filterXY*difCrd.x);
	 Trc[genTrcNum].genTrc.y=static_cast<float>(
		 difCrd.extrY+filterXY*difCrd.y);
	 if(difT>DIF_FILTER_V_T)
         {
	   Trc[genTrcNum].genTrc.vX+=static_cast<float>(
		   (Trc[genTrcNum].genTrc.x-difCrd.extrX)/(difT+filterV));
	   Trc[genTrcNum].genTrc.vY+=static_cast<float>(
		   (Trc[genTrcNum].genTrc.y-difCrd.extrY)/(difT+filterV));
	   Trc[genTrcNum].genTrc.v=static_cast<float>(
		   _hypot(static_cast<double>(Trc[genTrcNum].genTrc.vX),
                  static_cast<double>(Trc[genTrcNum].genTrc.vY)));
         if(Trc[genTrcNum].genTrc.vX==0.)
           Trc[genTrcNum].genTrc.vX=0.0001f;
	   Trc[genTrcNum].genTrc.psi=static_cast<float>(
		   atan2(static_cast<double>(Trc[genTrcNum].genTrc.vY),
           static_cast<double>(Trc[genTrcNum].genTrc.vX)));
         if(Trc[genTrcNum].genTrc.psi<0.0f)
           Trc[genTrcNum].genTrc.psi+=static_cast<float>(2.*M_PI);
	   }
       if ( Trc[genTrcNum].genTrc.trustXY > Msg.trustXY )
		   Trc[genTrcNum].genTrc.trustXY = Msg.trustXY;
	 return;
	 }

     // обработка при не попадании в строб сопровождения
     if(signX!=0)
       Trc[genTrcNum].genTrc.x=static_cast<float>(
		   difCrd.extrX+signX*filterXY*difFilter);
     else
       Trc[genTrcNum].genTrc.x=static_cast<float>(
		   difCrd.extrX+filterXY*difCrd.x);
     if(signY!=0)
       Trc[genTrcNum].genTrc.y=static_cast<float>(
		   difCrd.extrY+signY*filterXY*difFilter);
     else
       Trc[genTrcNum].genTrc.y=static_cast<float>(
		   difCrd.extrY+filterXY*difCrd.y);
     Trc[genTrcNum].genTrc.trustXY=Msg.trustXY;
     return;
     }

     //========================================
     // обновление высоты
     //========================================
     void TTrcProc::HUpdate(const TUTrcMsg &Msg,
                            TProcSituation *pSituation,
                            unsigned int genTrcNum,
							int i)
     {
     float h;
	 float trustH;
	 float ratio;
	 double difT;
     if(Msg.hBarUpdate==1)
       {
       // есть обновление барометрической высоты
       h=Msg.hBar;
       (*pSituation).Update[i].hUpdate=1;
       Trc[genTrcNum].genTrc.hBar=Msg.hBar;
       Trc[genTrcNum].genTrc.tHBarUpdate=Msg.t;
       }
    else
       // есть обновление р/л высоты
       h=Msg.h;
    // есть измерение р/л или барометрической высоты 
    difT=Msg.t-Trc[genTrcNum].genTrc.tHUpdate;
    trustH=Trc[genTrcNum].genTrc.trustH+((float)difT)*EXTENS_TRUST_H;
    ratio=trustH/(Msg.trustH+trustH);
    if((ratio>RATIO_CHANGE_H)||((*pSituation).Update[i].newTrc==1)||(Trc[genTrcNum].genTrc.sensCount==1))
       {
       // обновление высоты заменой
       (*pSituation).Update[i].hUpdate=1;
       Trc[genTrcNum].genTrc.h=h;
       Trc[genTrcNum].genTrc.tHUpdate=Msg.t;
       Trc[genTrcNum].genTrc.trustH=Msg.trustH;
       }
    else
       {
       if(ratio>RATIO_FILTER_H)
         {
          // обновление координат фильтрацией
         (*pSituation).Update[i].hUpdate=1;
         Trc[genTrcNum].genTrc.h=h*ratio+Trc[genTrcNum].genTrc.h*(1-ratio);
         Trc[genTrcNum].genTrc.tHUpdate=Msg.t;
         Trc[genTrcNum].genTrc.trustH=Msg.trustH;
         }
      else
          {
          //нет обновления
          }
        }
      }


	 //========================================
     // обновление признаков
     //========================================
     void TTrcProc::CharUpdate(const TUTrcMsg &Msg,
                             TProcSituation *pSituation,
                             TSensGenTrcLink **pLink,
                             unsigned int genTrcNum,
							 int i/*unsigned char sensAddGenTrc*/)
     {
     int trcNum;
     int sensNum;
     EUYesNo sensQualify;
     int hostileOGP;
     int mbFriendOGP;
     int friendOGP;
     EUYesNo manevr;
     unsigned char quant;

     if((Msg.xyUpdate==1)&&(Msg.indNum!=0))
       {
       // есть обновление индивидуального номера
       Trc[genTrcNum].genTrc.indNum =Msg.indNum;
       Trc[genTrcNum].genTrc.tIndNumUpdate=Msg.t;
       }

     // sensQualify=EU_NO;
     hostileOGP=0;
     mbFriendOGP=0;
     friendOGP=0;
     manevr=EU_NO;
     quant=0;
     for(sensNum=0;sensNum<SENS_MAX;sensNum++)
       {
       trcNum=Trc[genTrcNum].genTrc.sensTrcNum[sensNum];
       if(trcNum!=0)
         {
          // определение квалификации источника
           sensQualify=EU_YES;
        if(Trc[genTrcNum].genTrc.sensCount==1)
           sensQualify=EU_YES;
         if(sensQualify==EU_YES)
           {
           // источник квалифицированный
           // подсчёт ОГП
           if(Msg.OGPUpdate==1)
             {
             // есть обновление ОГП
             switch((*pLink[Msg.sensNum][Msg.trcNum].Data).OGP)
               {
               case EU_OGP_HOSTILE:
                 hostileOGP++;
                 break;
               case EU_OGP_MB_FRIEND:
                 mbFriendOGP++;
                 break;
               case EU_OGP_FRIEND:
                 friendOGP++;
                 break;
               default:
                 break;
               }
             }
           // подсчёт манёвра
           if(Msg.manevrUpdate==1)
             // есть обновление манёвра
             if((*pLink[Msg.sensNum][Msg.trcNum].Data).manevr==EU_YES)
               manevr=EU_YES;
           // подсчёт количественного состава
           if(Msg.quantUpdate==1)
             // есть обновление количественного состава
             if(quant<(*pLink[Msg.sensNum][Msg.trcNum].Data).quant)
               quant=(*pLink[Msg.sensNum][Msg.trcNum].Data).quant;
           }
         }
       }
     // формирование ОГП
     if(Msg.OGPUpdate==1)
       {
       Trc[genTrcNum].genTrc.tOGPUpdate=Msg.t;
       if(hostileOGP>(mbFriendOGP+friendOGP))
         Trc[genTrcNum].genTrc.OGP=EU_OGP_HOSTILE;
       else
         {
         if(friendOGP>0)
           Trc[genTrcNum].genTrc.OGP=EU_OGP_FRIEND;
         else
           {
           if(mbFriendOGP>0)
             Trc[genTrcNum].genTrc.OGP=EU_OGP_MB_FRIEND;
           }
         }
       }
     // формирование манёвра
     if(Msg.manevrUpdate==1)
       Trc[genTrcNum].genTrc.manevr=manevr;
     // формирование количественного состава
     if(Msg.quantUpdate==1)
       // есть обновление количественного состава
       Trc[genTrcNum].genTrc.quant=quant;

	 // Запись типов объекта.
	 /* происходит обновление тільки ненулевых признаков */
	 
     // запись категории объекта
	 Trc[genTrcNum].genTrc.objClass = UOC_AIR;
	 }

     //========================================
     //Сопровождение
     //========================================
     void TTrcProc::TrcUpdate(const TUTrcMsg &Msg,
                              /*TMsgProc* pMsgProc,*/
                              TProcSituation *pSituation,
                              TSensGenTrcLink **pLink)
     {
     double difT;
     float trustXY;
     // float trustH;
     float ratio;
     int sensQualityCount;
     // int sensNum;
     int i;
     unsigned int genTrcNum;
     EUYesNo sensQualify;
     // цикл по массиву решений
     for(i=0;i<2;i++)
       {
       if((*pSituation).Update[i].updateTrc==1)
         {
         // решение обновления
         genTrcNum=(*pSituation).Update[i].trcNum;
         sensQualify=EU_YES;
         if(Trc[genTrcNum].genTrc.sensCount>1)
           {
           // трасса обновляется несколькими источниками
           }
         if((*pSituation).Update[i].newTrc==1)
           {
           // образование новой трассы
           Trc[genTrcNum].genTrc.tStart=Msg.t;
           Trc[genTrcNum].genTrc.imitObj=Msg.imitObj;
           }
         // обновление координат
         if((Msg.xyUpdate==1)&&(sensQualify==EU_YES))
           {
           sensQualityCount=Trc[genTrcNum].genTrc.sensCount;
           difT=Msg.t-Trc[genTrcNum].genTrc.tXYUpdate;
           trustXY=Trc[genTrcNum].genTrc.trustXY+
			   (static_cast<float>(difT))*EXTENS_TRUST_XY;
           ratio=trustXY/Msg.trustXY;
           if((ratio>2.)||((*pSituation).Update[i].newTrc==1)||(sensQualityCount<=1))
             {
             // обновление координат заменой
             (*pSituation).Update[i].xyUpdate=1;
             ChangeUpdate(Msg,
                          pSituation,
                          genTrcNum);
             }
           else
             {
             if(ratio>0.5)
               {
               // обновление координат фильтрацией
               (*pSituation).Update[i].xyUpdate=1;
               FilterUpdate(Msg,
                           pSituation,
                           pLink,
                           genTrcNum);
               }
             else
               {
               //нет обновления
               }
             }
           }
         if(((Msg.hUpdate==1)||(Msg.hBarUpdate==1)))      //&&(sensQualify==EU_YES))
           // обновление высоты
           HUpdate(Msg,
                  pSituation,
                  genTrcNum,
				  i);
         // обновление признаков
         CharUpdate(Msg,
                    pSituation,
                    pLink,
                    genTrcNum,
                    i/*(*pSituation).Update[i].sensAdd*/);
         }
       }
     }


const TTrcProc::TProcSituation TTrcProc::TProcSituation::CSituation0 = {};

} // namespace air

} // namespace PTPV
