#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "TGeneralTrackSea.h"
#include "DefSea.h"
#include "TTrcProcSea.h"

#include "OSLibFacilitiesAccomodation.h"

namespace PTPV
{

namespace sea
{
	
const TGenTrcS CGenTrcS0 = {EU_NO};

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
	EMismatIdent  mismatIdent;           // несоответствие отождествления
                                            // 0 - соответствие
               		                        //_1 - несоотв-е по индив. номеру
		                                    //_2 - несоотв-е по XY и признакам
		                                    //_3 - несоотв-е по источн. сопров.
    
	// отбор при отождествлении
    struct TAliveSelect
	{   // отбор по координатам "живых"
		unsigned int num;  // номер отобранной обобщённой трассы
		double dist;       // расстояние до отобранной обобщённой трассы
	} aliveSelect[ALIVE_SELEKT_MAX];
	unsigned int selectCount;

	struct TDeadSelect
	{   // отбор по координатам "мёртвых"
		unsigned int num;  // номер отобранной обобщённой трассы
		double dist;       // номер отобранной обобщённой трассы
	} deadSelect;

	struct TIndNumbSelect
	{   // отбор по индивидуальному номеру
		unsigned int num;     // номер отобранной обобщённой трассы
		float dist;           // // расстояние до отобранной обобщённой трассы
		char reTrc;           // замена старого решения
		} indNumbSelect;

    unsigned char  error;    // ошибка при обработке сообщения

    // ситуации по обобщённой трассе
	struct TUpdate
	{
		unsigned int  trcNum;        // номер трассы в системе ТОИ
		unsigned char newTrc;        // признак новой обобщенной трассы
		unsigned char sensAdd;       // вписывание источника:
					                 // 1 - безусловное отождествление,
					                 // 2 - условное отождествление по ОГП,
					                 // 4 - условное отождествление по H,
					                 // 6 - условное отождествление по H и ОГП 
		unsigned char sensDelete;    // вычёркивание источника
		unsigned char updateTrc;     // обновление обобщенной трассы

		// обновление  признаков
	    unsigned char  xyUpdate;     // обновлениe X,Y
		unsigned char  hUpdate;      // обновлениe h
		unsigned char  OGPUpdate;    // обновлениe ОГП
		unsigned char  OGPChange;    // изменение ОГП
		unsigned char  SOSChange;    // изменениe бедствия
		unsigned char  indNum;       // первый приход (вписывание) инд. ном.
	} Update[2];
	
	static const TProcSituation CSituation0;
	}; // struct TProcSituation


     //========================================
     //Диспетчер процесса обработки сообщений
     //=======================================
     void TTrcProc::MsgTaskChain(const TUTrcMsg *pMsg,
                                   TMsgProc* pMsgProc,
                                   TSensGenTrcLink **pLink)
     {
     // инициализация и обнуление зоны ситуаций обработки 
     TProcSituation *pSituation;
     pSituation=new TProcSituation(TProcSituation::CSituation0);
     // диспетчеризация
     // анализ входного сообщения
     MsgCheck(pMsg,
              pSituation,
              pLink);
     if(((*pSituation).newTrc==1)||((*pSituation).sequentialSolution==1))
       // отождествление 
       Ident(pMsg,pSituation,pLink);
     if((*pSituation).oldTrc==1)
       //Оценка соответствия первичного отождествления
       IdentCheck(pMsg,
                  pSituation,
                  pLink);
/*     if((*pSituation).mismatIdent==MI_IND_NUM)
       ReIdentIndNum(pMsg,
                  pSituation,
                  pLink);*/
     if((*pSituation).mismatIdent==MI_SENS)
       ReIdentSens(pMsg,
                  pSituation,
                  pLink);
     if((*pSituation).mismatIdent==MI_CRD)
       ReIdentCrd(pMsg,
                  pSituation,
                  pLink);
     if(((*pSituation).Update[0].sensAdd==1)||
        ((*pSituation).Update[0].sensDelete==1)||
        ((*pSituation).Update[0].newTrc==1)||
        ((*pSituation).Update[1].sensAdd==1)||
        ((*pSituation).Update[1].sensDelete==1)||
        ((*pSituation).Update[1].newTrc==1))
       //Реализация решения отождествления
       SolutionApply(pMsg,
                     pSituation,
                     pLink);
     if(((*pSituation).Update[0].updateTrc==1)||((*pSituation).Update[1].updateTrc==1))
       {
       // обновление обобщённой трассы
       TrcUpdate(pMsg,
                   /*pMsgProc,*/
                   pSituation,
                   pLink);
       //формирование выходного решения ТОИ 
       SolusionRecord(pMsg,
                      pMsgProc,
                      pSituation/*,
                      pLink*/);
       } 
     // освобождение зоны ситуаций обработки 
     delete pSituation;
     }


     //============================================== 
     //Анализ ситуации обработки
     //===============================================
     void TTrcProc::MsgCheck(const TUTrcMsg *pMsg,
                               TProcSituation *pSituation,
                               TSensGenTrcLink **pLink)
     {
     if((*pMsg).trcState==EU_TS_END)
       {
       if(pLink[pMsg->sensNum][pMsg->trcNum].genTrc==0)
         {    // а если не была заведена!!!
         // сброс трассы источника
         SensTrcEnd(pMsg->sensNum,
                    pMsg->trcNum,
                    pLink);
         // статус трассы источника - не отождествлена
         pLink[pMsg->sensNum][pMsg->trcNum].identState=IS_NONE;
         return;
         }
       (*pSituation).Update[0].trcNum=pLink[(*pMsg).sensNum][(*pMsg).trcNum].genTrc;
       (*pSituation).Update[0].sensDelete=1;
       (*pSituation).sensTrcEnd=1;
       (*pSituation).Update[0].updateTrc=1;
       }
     else
       {
         switch(pLink[pMsg->sensNum][pMsg->trcNum].identState)
         {
         case 0:
           SensTrcNew((*pMsg).sensNum,(*pMsg).trcNum,pLink);
           (*pSituation).newTrc=1;
           break;
         case 1:
           (*pSituation).sequentialSolution=1;
           break;
         default:
           (*pSituation).oldTrc=1;
           (*pSituation).Update[0].trcNum=pLink[(*pMsg).sensNum][(*pMsg).trcNum].genTrc;
         }
       }
     (*pLink[(*pMsg).sensNum][(*pMsg).trcNum].Data).tLastMsg=/*(*pMsg).t*/ pMsg->msgTime; // тимчасово!
     (*pLink[(*pMsg).sensNum][(*pMsg).trcNum].Data).OGP=(*pMsg).OGP;
     (*pLink[(*pMsg).sensNum][(*pMsg).trcNum].Data).manevr=(*pMsg).manevr;
     if((*pMsg).indNum!=0)
       (*pLink[(*pMsg).sensNum][(*pMsg).trcNum].Data).tIndNumUpdate=(*pMsg).t;
     }

     //====================================================
     //Отождествление
     //====================================================
     void TTrcProc::Ident(const TUTrcMsg *pMsg,
                           TProcSituation *pSituation,
                           TSensGenTrcLink **pLink)
       {
/*     //  отождествление по индивидуальному номеру 
       if((*pMsg).indNum!=0)
         {
         // есть инд. нoмер
         // Отбор по инд. номеру
         IndNumSelect(pMsg,
                      pSituation,
                      pLink);
         if((*pSituation).indNumbSelect.num!=0)
           {
           // есть отобранные по индивидуальному номеру
           // вписывание источника в отобранную обобщённую трассу
           (*pSituation).Update[0].sensAdd=1;
           (*pSituation).Update[0].trcNum=(*pSituation).indNumbSelect.num;
           SeqentialSolutionDelete((*pMsg).sensNum,(*pMsg).trcNum,pLink);
           if((*pSituation).indNumbSelect.reTrc!=0)
             // замена трассы источника в отобранной обобщённой трассе
             (*pSituation).Update[0].sensDelete=1;
           // произошло отождествление по индивидуальному номеру
           return;
           }
         } */
       // отождествление по координатам 
       // отбор по координатам 
       CrdSelect(pMsg,
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
             SeqentialSolutionDelete((*pMsg).sensNum,(*pMsg).trcNum,pLink);
             break;
             }
           case 1:
             {
             // отобрана только одна трасса
             if((*pSituation).aliveSelect[0].dist<DIF_IDENT_XY)
               {
               //отобранная трасса в стробе отождествления - отождествление
               (*pSituation).Update[0].sensAdd=1;
               (*pSituation).Update[0].trcNum=(*pSituation).aliveSelect[0].num;
               SeqentialSolutionDelete((*pMsg).sensNum,(*pMsg).trcNum,pLink);
               break;
               }
             }
           default:
             {
             // есть несколько отобранных Или отобраннаяв стробе отождествления -
             // запись на последовательный анализ
             pLink[(*pMsg).sensNum][(*pMsg).trcNum].identState=IS_FIRST;
             (*pLink[(*pMsg).sensNum][(*pMsg).trcNum].SeqSolution).num=
             (*pSituation).aliveSelect[0].num;
             (*pLink[(*pMsg).sensNum][(*pMsg).trcNum].SeqSolution).step=1;
             (*pLink[(*pMsg).sensNum][(*pMsg).trcNum].SeqSolution).MIN=
             (*pSituation).aliveSelect[0].dist;
             }
           }
         }
       else
         {
         // трасса источника на последовательном анализе  
         if((*pSituation).aliveSelect[0].dist<DIF_IDENT_XY)
           {
           //отобранная трасса в стробе отождествления - отождествление
           (*pSituation).Update[0].sensAdd=1;
           (*pSituation).Update[0].trcNum=(*pSituation).aliveSelect[0].num;
           SeqentialSolutionDelete((*pMsg).sensNum,(*pMsg).trcNum,pLink);
           }
         else
           {
           // отобранная трасса не в стробе отождествления -
           // формирование новой трассы
           (*pSituation).Update[0].newTrc=1;
           SeqentialSolutionDelete((*pMsg).sensNum,(*pMsg).trcNum,pLink);
           }
         }
       }

     //=================================================
     //Реализация отождествления
     //=================================================
     void TTrcProc::SolutionApply(const TUTrcMsg *pMsg,
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
            SensTrcDelete((*pMsg).sensNum,
                          Trc[genTrcNum].genTrc.sensTrcNum[(*pMsg).sensNum],
                          pLink);
          if((*pSituation).sensTrcEnd==1)
            // сброс трассы источника
            SensTrcEnd((*pMsg).sensNum,
                            (*pMsg).trcNum,
                            pLink);
	    if((*pSituation).Update[i].sensAdd!=0)
	      {
            // вписывание источника
            SensTrcAdd(genTrcNum,
                           (*pMsg).sensNum,
                           (*pMsg).trcNum,
                           pLink);
	      (*pSituation).Update[i].updateTrc=1;
	      if((*pSituation).Update[i].sensAdd!=1)
		  {
              // вписывание признака условного отождествления
		  if((*pSituation).Update[i].sensAdd==2)
                // условное отождествление по ogp
		    pLink[(*pMsg).sensNum][(*pMsg).trcNum].identState=IS_CONDITION_OGP;
		  if((*pSituation).Update[i].sensAdd==4)
                // условное отождествление по h
		    pLink[(*pMsg).sensNum][(*pMsg).trcNum].identState=IS_CONDITION_H;
		  if((*pSituation).Update[i].sensAdd==6)
                // условное отождествление по ogp и h
		    pLink[(*pMsg).sensNum][(*pMsg).trcNum].identState=IS_CONDITION_OGP_H;
		  }
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
                            (*pMsg).sensNum,
                            (*pMsg).trcNum,
                            pLink);
              // запись признака обновления обобщённой трассы
              (*pSituation).Update[i].updateTrc=1;
	        }
            else ;
              // свободный формуляр не найден
              // окончание работы по данному решению
            }
          }
        }
      }


     //========================================
     //Сопровождение
     //========================================
     void TTrcProc::TrcUpdate(const TUTrcMsg *pMsg,
                              /*TMsgProc* pMsgProc,*/
                              TProcSituation *pSituation,
                              TSensGenTrcLink ** /*pLink*/)
     {
     int i;
     for(i=0;i<2;i++)
       {
       if((*pSituation).Update[i].updateTrc==1)
         {
         ReUpdate(pMsg,
                  pSituation,
                  i);
         }
       }
     }

     //========================================
     // простое обновление
     //========================================
     void TTrcProc::ReUpdate(const TUTrcMsg *pMsg,
                             TProcSituation *pSituation,
                             int i)
{
     const unsigned int genTrcNum = (*pSituation).Update[i].trcNum;
     EUYesNo sensQualiny;
     sensQualiny=EU_YES;
     if(Trc[(*pSituation).Update[i].trcNum].genTrc.sensCount>1)
       {
		   ;
       }
     if((*pSituation).Update[i].newTrc==1)
       {
       // образование новой трассы
       Trc[genTrcNum].genTrc.tStart=(*pMsg).t;
       Trc[genTrcNum].genTrc.imitObj=(*pMsg).imitObj;
       }
     if ( ((*pMsg).xyUpdate==1)&&(sensQualiny==EU_YES) )
       {
       // есть обновление координат
       (*pSituation).Update[i].xyUpdate=1;
       Trc[genTrcNum].genTrc.tXYUpdate=(*pMsg).t;
       Trc[genTrcNum].genTrc.x=(*pMsg).x;
       Trc[genTrcNum].genTrc.y=(*pMsg).y;
       Trc[genTrcNum].genTrc.v=(*pMsg).v;
       Trc[genTrcNum].genTrc.psi=(*pMsg).psi;
       Trc[genTrcNum].genTrc.vX=(*pMsg).vX;
       Trc[genTrcNum].genTrc.vY=(*pMsg).vY;
       Trc[genTrcNum].genTrc.trustXY=(*pMsg).trustXY;
       }
     if((*pMsg).hUpdate==1)
       {
       // есть обновление высоты
       (*pSituation).Update[i].hUpdate=1;
       Trc[genTrcNum].genTrc.h=(*pMsg).h;
       Trc[genTrcNum].genTrc.tHUpdate=(*pMsg).t;
       Trc[genTrcNum].genTrc.trustH=(*pMsg).trustH;
       }
     if((*pMsg).hBarUpdate==1)
       {
       // есть обновление барометрической высоты
       (*pSituation).Update[i].hUpdate=1;
       Trc[genTrcNum].genTrc.hBar=(*pMsg).hBar;
       Trc[genTrcNum].genTrc.tHBarUpdate=(*pMsg).t;
       Trc[genTrcNum].genTrc.trustH=(*pMsg).trustH;
       }
     if((*pMsg).indNum!=0)
       {
       // есть обновление индивидуального номера
       Trc[genTrcNum].genTrc.indNum =(*pMsg).indNum;
       Trc[genTrcNum].genTrc.tIndNumUpdate=(*pMsg).t;
       }
     if((*pMsg).OGPUpdate==1)
       {
       // есть обновление ОГП
       Trc[genTrcNum].genTrc.OGP =(*pMsg).OGP;
       Trc[genTrcNum].genTrc.tOGPUpdate=(*pMsg).t;
       }
     if((*pMsg).manevrUpdate==1)
       // есть обновление манёвра
       Trc[genTrcNum].genTrc.manevr =(*pMsg).manevr;
     if((*pMsg).quantUpdate==1)
       // есть обновление количественного состава
       Trc[genTrcNum].genTrc.quant =(*pMsg).quant;
     
	 // Запись типов объекта.
	 /* происходит обновление тільки ненулевых признаков */
	 
	 // запись класса объекта
	 Trc[genTrcNum].genTrc.objClass = pMsg->objClass;
}

     //==========================================
     //формирование выходного решения ТОИ 
     //=============================================
     void TTrcProc::SolusionRecord(const TUTrcMsg *pMsg,
                                TMsgProc* pMsgProc,
                                TProcSituation *pSituation/*,
                                TSensGenTrcLink **pLink*/)
     {
     int i;
	 (*pMsgProc).error=(*pSituation).error;
     for(i=0;i<2;i++)
	   {
       if((*pSituation).Update[i].updateTrc==1)
         {
         (*pMsgProc).Update[i].trcNum=(*pSituation).Update[i].trcNum;
         (*pMsgProc).Update[i].newTrc=(*pSituation).Update[i].newTrc;
		 (*pMsgProc).Update[i].trcUpdate=(*pSituation).Update[i].updateTrc;
         (*pMsgProc).Update[i].sensAdd=(*pSituation).Update[i].sensAdd;
         (*pMsgProc).Update[i].sensDelete=(*pSituation).Update[i].sensDelete;
         (*pMsgProc).Update[i].OGPChange=(*pSituation).Update[i].OGPChange;
         (*pMsgProc).Update[i].xyUpdate=(*pSituation).Update[i].xyUpdate;
         (*pMsgProc).Update[i].hUpdate=(*pSituation).Update[i].hUpdate;
         }
       }
     }
//---------------------------------------------------------------------------------------------------
     //================================================
     //Диспетчер периодического контроля статуса
     //================================================
      void TTrcProc::StateTaskChain(const bool, TStateProc* pStateProc,
                                    TSensGenTrcLink **pLink,
                                    const TSensorDescription *sensorDescription)
      {
      StateCheck(pStateProc, pLink, sensorDescription);
      if((*pStateProc).genTrcDrop==1)
        GenTrcEnd((*pStateProc).genTrcNum);
      }

      //=================================================
      //проверка статуса трассы
      //=================================================
      void TTrcProc::StateCheck(TStateProc* pStateProc,
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
            if ( (*pStateProc).currentT-pLink[sensNum][trcNum].Data->tLastMsg >
                 2. * sensorDescription[sensNum].dataTemp )
              {
              // источник не присылает донесений по данной трассе более ?? темпов поступления информации
              (*pStateProc).sensTrcDelete[sensNum]=trcNum;
			  (*pStateProc).sensTrcDrop = EU_YES;
              // вычёркивание трассы источника
              SensTrcDelete(sensNum,
                           (*pStateProc).sensTrcDelete[sensNum],
                           pLink);
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
      if((Trc[(*pStateProc).genTrcNum].genTrc.sensCount==0))
        {
        if(Trc[(*pStateProc).genTrcNum].genTrcT.tHold<(*pStateProc).currentT)
          // истекло время хранения 
            (*pStateProc).genTrcDrop=1;
        }
      }

	// корректировка состояния третичной обработки при стирании информации
	// о трассах источников, сопровождающих обобщённые трассы
	int TTrcProc::OnSensErasing(bool taskStart, unsigned int genTrcNum)
	{
		if ( Trc[genTrcNum].genTrc.sensCount )
			Trc[genTrcNum].genTrcT.tHold = ErasingHoldTime(genTrcNum);
		return 1;
	}
	
     //=============================================
     //Сброс обобщённой трассы
     //============================================
     void TTrcProc:: GenTrcEnd(unsigned int genTrcNum)
     {
     Trc.DestroyRecord(genTrcNum);
     Trc[genTrcNum].genTrcT.busyState= EU_NO;
     }

//--------------------------------------------------------------------------------------------

      //=================================================
      // организация новой трассы от источника
      //===============================================
      void TTrcProc::SensTrcNew(unsigned int sensNum,
                                  unsigned int trcNum,
                                  TSensGenTrcLink **pLink)
         {
         // запрос памяти для даных, присылаемых источником
         pLink[sensNum][trcNum].Data=new TSensTrcData;
         // запрос памяти для даных, используемых последовательным анализом
         pLink[sensNum][trcNum].SeqSolution=new TSeqSolution;
         }

      //=============================================
      // сброс трассы источника
      //===============================================
      void TTrcProc::SensTrcEnd(unsigned int sensNum,
                                   unsigned int trcNum,
                                   TSensGenTrcLink **pLink)
         {
         // освобождение памяти для даных, присылаемых источником
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
                                  TSensGenTrcLink **pLink)
        {
        // статус трассы источника - отождествлена
        pLink[sensNum][trcNum].identState=IS_IDENT;
        // вписывание связки трассы источника с обобщённой трассой
        pLink[sensNum][trcNum].genTrc= genTrcNum;
        // вписывание источника соповождения в обобщённую трассу
        Trc[genTrcNum].genTrc.sensTrcNum[sensNum]=trcNum;
        Trc[genTrcNum].genTrc.sensCount ++ ;
        // освобождение памяти для даных, используемых последовательным анализом
        SeqentialSolutionDelete(sensNum,trcNum,pLink);
        }
 
     //=======================================================
     // вычёркивание трассы источника из обобщённой трассы
     //=======================================================
     void TTrcProc::SensTrcDelete(unsigned int sensNum,
                                     unsigned int trcNum,
                                     TSensGenTrcLink **pLink)
        {
        // вычёркивание источника соповождения из обобщённой трассы
        Trc[pLink[sensNum][trcNum].genTrc].genTrc.sensTrcNum[sensNum]=0;
        Trc[pLink[sensNum][trcNum].genTrc].genTrc.sensCount --;
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

	//=================================================
	// Определение времени хранения трассы с принудит-но стёртыми источниками
	//=================================================
	double TTrcProc::ErasingHoldTime(unsigned int genTrcNum)
	{
		return Trc[genTrcNum].genTrc.tXYUpdate + DIF_ERASE_T;
	}

	 //========================================
     // отбор обобщённых трасс по координатам
     //========================================
     void TTrcProc::CrdSelect(const TUTrcMsg *pMsg,
                              TProcSituation *pSituation)
       {
       int genTrcNum;
       int selectNum;
       int selectCount;
       double difPsi;
       //float difH;
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
       for(genTrcNum=1;genTrcNum<=UGEN_SURFACE_TRC_MAX;genTrcNum++)
         {
         //  анализ признака занятости формуляра 
         if(Trc[genTrcNum].genTrcT.busyState==EU_NO)
           continue;
         //  анализ признакoв тренажа на равенствo 
         if((*pMsg).imitObj!=Trc[genTrcNum].genTrc.imitObj)
           continue;
/*       //  анализ признакoв OGP на непротиворечивсть 
         if(((*pMsg).OGP!=OGP_UNKNOWN)&&(Trc[genTrcNum].genTrc.OGP!=OGP_UNKNOWN))
           { 
           if((*pMsg).OGP!=Trc[genTrcNum].genTrc.OGP)
             {
             if(((*pMsg).OGP==OGP_HOSTILE)||(Trc[genTrcNum].genTrc.OGP==OGP_HOSTILE))
               continue;
             }
           }*/
	   if(Trc[genTrcNum].genTrc.sensCount==0)
           {
           // обобщенная трасса "мертвая"
           // анализ курсoв трасс,
           difPsi=Trc[genTrcNum].genTrc.psi-(*pMsg).psi;
	     if(difPsi<0)
             difPsi= -difPsi;
           if(difPsi>DIF_DEAD_PSI)
             continue;
           }
         // анализ источника сопровождения
         if(Trc[genTrcNum].genTrc.sensTrcNum [(*pMsg).sensNum]!=0)
           continue;
/*         // анализ высот
         if((*pMsg).hUpdate==1)
           {
           // в пришедшем сообщении обновлена высота 
           difH=Trc[genTrcNum].genTrc.h-(*pMsg).h;
	     if(difH<0)
             difH= -difH;
           if(difH>DIF_H)
             continue;
           }*/
         // анализ координат
         difT=(*pMsg).t-Trc[genTrcNum].genTrc.tXYUpdate;
         // экстраполяция и проверка по стробу координаты x
         difCrd.x=fabs(Trc[genTrcNum].genTrc.x+Trc[genTrcNum].genTrc.vX*difT-(*pMsg).x);
         if((difCrd.x)>DIF_XY)
           continue;
         // экстраполяцияи проверка по стробу координаты y
         difCrd.y=fabs(Trc[genTrcNum].genTrc.y+Trc[genTrcNum].genTrc.vY*difT-(*pMsg).y);
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
/*
     //====================================================
     // отбор обобщённых трасс по индивидуальному номеру
     //====================================================
     void TTrcProc::IndNumSelect(TTrcMsg* pMsg,
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
       selectCount=0;
       for(genTrcNum=2;genTrcNum<=GEN_SEA_TRC_MAX;genTrcNum++)
         {
         //  анализ признака занятости формуляра 
         if(Trc[genTrcNum].genTrcT.busyState==NO)
           continue;
         //  анализ признакoв тренажа на равенствo 
         if((*pMsg).imitObj!=Trc[genTrcNum].genTrc.imitObj)
           continue;
         //  анализ линии запроса инд. нoмерoв 
         if(((*pMsg).reqLine!=REQ_LINE_PASSWORD)||
            ((*pMsg).reqLine!=REQ_LINE_RAINBOW))
           {
           //  отбор по номеру "ПАРОЛЬ"
           if(Trc[genTrcNum].genTrc.indNum!=0)
             {
             reTrc=0;
             // во входном донесении и в обобщённой трассе
             // есть инд. номер "ПАРОЛЬ"
             if((*pMsg).indNum!=Trc[genTrcNum].genTrc.indNum)
               // номера различны - нет отождествления
               continue;
             // анализ источника сопровождения
             sensTrcNum=Trc[genTrcNum].genTrc.sensTrcNum[(*pMsg).sensNum];
             if(sensTrcNum!=0)
               {
               // источник сопровождает отбираемую трассу
               if(((*pMsg).t-(*pLink[(*pMsg).sensNum][sensTrcNum].Data).tIndNumUpdate)<
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
             if(((*pSituation).PGSMsg==YES)||((Trc[genTrcNum].genTrc.sensCount==1)&&
                                  (Trc[genTrcNum].genTrc.sensTrcNum[9]!=0)))
               {
               // одна из трасс является трассой БСУНа - отождествляется без анализа 
               // координат
               //(*pSituation).indNumbSelect.dist=dist;
               (*pSituation).indNumbSelect.num=genTrcNum;
               (*pSituation).indNumbSelect.reTrc=reTrc;
               break;
               }
             else
               {
               // анализ координат
               difT=(*pMsg).t-Trc[genTrcNum].genTrc.tXYUpdate;
               // экстраполяция координаты x
               difCrd.x=fabs(Trc[genTrcNum].genTrc.x+Trc[genTrcNum].genTrc.vX*difT-(*pMsg).x);
               // экстраполяция координаты y
               difCrd.y=fabs(Trc[genTrcNum].genTrc.y+Trc[genTrcNum].genTrc.vY*difT-(*pMsg).y);
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
       }
*/
     //=================================
     // контроль Отождествления
     //=================================
     void TTrcProc::IdentCheck(const TUTrcMsg *pMsg,
                               TProcSituation *pSituation,
                               TSensGenTrcLink **pLink)
         {
       int genTrcNum;
       //int sensTrcNum;
       //int i;
       double difT;
       double difH;
       double dist;
       struct
         {
         double x;
         double y;
         } difCrd;
       //int quant;

         genTrcNum=(*pSituation).Update[0].trcNum;
         //проверка обновления по xy
         if((*pMsg).xyUpdate==0)
           {
           // обновления координат нет - нет возможности переотождествления
           (*pSituation).Update[0].updateTrc=1;
           return;
           }
/*
         // анализ индивидуального номера
         //  анализ линии запроса инд. нoмерoв 
         if(((*pMsg).reqLine!=REQ_LINE_PASSWORD)||
            ((*pMsg).reqLine!=REQ_LINE_RAINBOW))
           {
           //  анализ по номеру "ПАРОЛЬ"
           if(Trc[genTrcNum].genTrc.indNum!=0)
             {
             // во входном донесении и в обобщённой трассе
             // есть инд. номер "ПАРОЛЬ"
             if((*pMsg).indNum!=Trc[genTrcNum].genTrc.indNum)
               {
               // номера различны
               quant=0;
               for(i=1;i<=SENS_MAX;i++)
                 {
                 sensTrcNum=Trc[genTrcNum].genTrc.sensTrcNum[i];
                 if(sensTrcNum==0)
                   continue;
                 if(((*pMsg).t-(*pLink[i][sensTrcNum].Data).tIndNumUpdate)<
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
           }
*/
         // источник сопровождения один
         if(Trc[genTrcNum].genTrc.sensCount==1)
           {
           Trc[genTrcNum].genTrcT.mismatSensCount++;
           if(Trc[genTrcNum].genTrcT.mismatSensCount>=MISMAT_SENS_COUNT)
             {
             if((*pMsg).OGP!=EU_OGP_UNKNOWN)
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
         if((*pMsg).imitObj!=Trc[genTrcNum].genTrc.imitObj)
           {
           // сообщение не соответствует обобщенной трассе по
           // признаку тренажа
           (*pSituation).mismatIdent=MI_CRD;
           (*pLink[(*pMsg).sensNum][(*pMsg).trcNum].Data).mismatXYCount=0;
           return;
           }
         // проверка условного отождествления по ОГП
         if ((pLink[pMsg->sensNum][pMsg->trcNum].identState==IS_CONDITION_OGP)||
             (pLink[pMsg->sensNum][pMsg->trcNum].identState==IS_CONDITION_OGP_H))
           {
           if ((*pMsg).OGPUpdate==1) 
             {
             // есть измерение  ОГП
             // стирание условного отождествления по ОГП
             if (pLink[pMsg->sensNum][pMsg->trcNum].identState==IS_CONDITION_OGP)
               pLink[pMsg->sensNum][pMsg->trcNum].identState=IS_IDENT;
             else
               pLink[pMsg->sensNum][pMsg->trcNum].identState=IS_CONDITION_H;
             if((*pMsg).OGP!=Trc[genTrcNum].genTrc.OGP) 
               {
               if (((*pMsg).OGP==1)||(Trc[genTrcNum].genTrc.OGP==1))
                 {
                 // если ОГП = 1 
                 // сообщение не соответствует обобщенной трассе по ОГП
                 // Выход на переотождествление по XY
                 (*pSituation).mismatIdent=MI_CRD;
                 (*pLink[(*pMsg).sensNum][(*pMsg).trcNum].Data).mismatXYCount=0;
                 return;
                 }
               }
             }
           }
         // проверка условного отождествления по высоте
         if ((pLink[pMsg->sensNum][pMsg->trcNum].identState==IS_CONDITION_H)||
             (pLink[pMsg->sensNum][pMsg->trcNum].identState==IS_CONDITION_OGP_H))
           {
           if ((*pMsg).hUpdate==1) 
             {
             // в пришедшем сообщении обновлена высота 
             // стирание условного отождествления по высоте
             if (pLink[pMsg->sensNum][pMsg->trcNum].identState==IS_CONDITION_H)
               pLink[pMsg->sensNum][pMsg->trcNum].identState=IS_IDENT;
             else
               pLink[pMsg->sensNum][pMsg->trcNum].identState=IS_CONDITION_OGP;           
             difH=Trc[genTrcNum].genTrc.h-(*pMsg).h;
  	       if(difH<0)
               difH= -difH;
             if(difH>DIF_H)
               {
               // сообщение не соответствует обобщенной трассе по высоте
               // Выход на переотождествление по XY
               (*pSituation).mismatIdent=MI_CRD;
               (*pLink[(*pMsg).sensNum][(*pMsg).trcNum].Data).mismatXYCount=0;
               return;
               }
             }  
           }
         // анализ координат
         difT=(*pMsg).t-Trc[genTrcNum].genTrc.tXYUpdate;
         // экстраполяция координаты x
         difCrd.x=fabs(Trc[genTrcNum].genTrc.x+Trc[genTrcNum].genTrc.vX*difT-(*pMsg).x);
         // экстраполяция координаты y
         difCrd.y=fabs(Trc[genTrcNum].genTrc.y+Trc[genTrcNum].genTrc.vY*difT-(*pMsg).y);
         // вычисление расстояния
         dist=sqrt(difCrd.x*difCrd.x+difCrd.y*difCrd.y);
         if(dist<DIF_CHECK_XY)
           {
           // сообщение соответствует обобщенной трассе по  XY
           (*pSituation).Update[0].updateTrc=1;
           (*pLink[(*pMsg).sensNum][(*pMsg).trcNum].Data).mismatXYCount=0;
           return;
           }
         (*pLink[(*pMsg).sensNum][(*pMsg).trcNum].Data).mismatXYCount++;
         if((*pLink[(*pMsg).sensNum][(*pMsg).trcNum].Data).mismatXYCount
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
         (*pLink[(*pMsg).sensNum][(*pMsg).trcNum].Data).mismatXYCount=0;
         return;
         }
/*
     //==============================================
     // переотождествление по индивидуальному номеру
     //===============================================
     void TTrcProc::ReIdentIndNum(TTrcMsg* pMsg,
                                  TProcSituation *pSituation,
                                  TSensGenTrcLink **pLink)
       {
       // Отбор по инд. номеру
       IndNumSelect(pMsg,
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
         SeqentialSolutionDelete((*pMsg).sensNum,(*pMsg).trcNum,pLink);
         if((*pSituation).indNumbSelect.reTrc!=0)
           // замена трассы источника в отобранной обобщённой трассе
           (*pSituation).Update[1].sensDelete=1;
         // произошло отождествление по индивидуальному номеру
         return;
         }
       // нет отобранных - формирование новой трассы
       (*pSituation).Update[1].newTrc=1;
       SeqentialSolutionDelete((*pMsg).sensNum,(*pMsg).trcNum,pLink);
       }
*/
     //======================================
     // переотождествление по координатам 
     //======================================
     void TTrcProc::ReIdentCrd(const TUTrcMsg *pMsg,
                                  TProcSituation *pSituation,
                                  TSensGenTrcLink **pLink)
       {
       // отбор по координатам 
       CrdSelect(pMsg,
                 pSituation);
       if((*pSituation).selectCount!=0)
         {
         // есть отобраные трассы
         if((*pSituation).aliveSelect[0].dist<DIF_IDENT_XY)
           {
           //отобранная трасса в стробе отождествления - отождествление
           // вычёркивание источника из старой обобщённой трассы
           (*pSituation).Update[0].sensDelete=1;
           // вписывание источника в отобранную обобщённую трассу
           (*pSituation).Update[1].sensAdd=1;
           (*pSituation).Update[1].trcNum=(*pSituation).aliveSelect[0].num;
           SeqentialSolutionDelete((*pMsg).sensNum,(*pMsg).trcNum,pLink);
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
       SeqentialSolutionDelete((*pMsg).sensNum,(*pMsg).trcNum,pLink);
       }
 
     //========================================
     // переотождествление по источнику
     //======================================
     void TTrcProc::ReIdentSens(const TUTrcMsg *pMsg,
                                TProcSituation *pSituation,
                                TSensGenTrcLink **pLink)
       {
       // отбор по координатам 
       CrdSelect(pMsg,
                 pSituation);
       if((*pSituation).selectCount!=0)
         {
         // есть отобраные трассы
         if((*pSituation).aliveSelect[0].dist<DIF_IDENT_XY)
           {
           //отобранная трасса в стробе отождествления - отождествление
           if((Trc[(*pSituation).aliveSelect[0].num].genTrc.sensCount==1)&&
              (Trc[(*pSituation).aliveSelect[0].num].genTrc.tStart>
               Trc[(*pSituation).Update[0].trcNum].genTrc.tStart))
             {
             // отобранная трасса сопровождается одном источником и старше
             // отождествляемой - сохранение старого решения
             (*pSituation).Update[0].updateTrc=1;
             return;
             }
           // отождествление с отобранной трассой
           // вычёркивание источника из старой обобщённой трассы
           (*pSituation).Update[0].sensDelete=1;
           // вписывание источника в отобранную обобщённую трассу
           (*pSituation).Update[1].sensAdd=1;
           (*pSituation).Update[1].trcNum=(*pSituation).aliveSelect[0].num;
           SeqentialSolutionDelete((*pMsg).sensNum,(*pMsg).trcNum,pLink);
           // произошло отождествление по координатам
           return;
           }
         }
       // нет отобранных, в стробе отождествления трасс
             // отождествляемой - сохранение старого решения
             (*pSituation).Update[0].updateTrc=1;
       }


	 const TTrcProc::TProcSituation TTrcProc::TProcSituation::CSituation0 = {};

} // namespace sea

} // namespace PTPV
