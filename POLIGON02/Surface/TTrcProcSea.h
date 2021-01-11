
              //
#ifndef _TTRCPROCSEA_H
#define _TTRCPROCSEA_H

#include "AdjustmentCommon.h"
#include "HSea.h"
#include "TGeneralTrackSea.h"

#include "DefSea.h"
#include "ESea.h"


namespace PTPV
{

namespace sea
{
using namespace COMMON::_PTPV_;

extern const TGenTrcS CGenTrcS0;  // нулевой формуляр зоны обобщённых трасс 

class TTrcProc
{
private:

	struct TProcSituation;    // тип состояния решений по входному сообщению

	TGeneralTrack &Trc;

  public:


      // диспетчер процесса обработки сообщений
      void MsgTaskChain(const TUTrcMsg *pMsg,
                        TMsgProc *pMsgProc,
                        TSensGenTrcLink **pLink);
      // анализ ситуации по входному сообщению 
      void MsgCheck(const TUTrcMsg *pMsg,
                    TProcSituation *pSituation,
                    TSensGenTrcLink **pLink);
      // отождествление 
      void Ident(const TUTrcMsg *pMsg,
                 TProcSituation *pSituation,
                 TSensGenTrcLink **pLink);

      // отбор обобщённых трасс по координатам
      void CrdSelect(const TUTrcMsg *pMsg,
                     TProcSituation *pSituation);

     // отбор обобщённых трасс по индивидуальному номеру
//      void IndNumSelect(const TUTrcMsg *pMsg,
//                        TProcSituation *pSituation,
//                        TSensGenTrcLink **pLink);

      // Преотождествление
//      void ReIdentIndNum(const TUTrcMsg *pMsg,
//                   TProcSituation *pSituation,
//                   TSensGenTrcLink **pLink);

      // Преотождествление
      void ReIdentCrd(const TUTrcMsg *pMsg,
                      TProcSituation *pSituation,
                      TSensGenTrcLink **pLink);

      // Преотождествление
      void ReIdentSens(const TUTrcMsg *pMsg,
                       TProcSituation *pSituation,
                       TSensGenTrcLink **pLink);
      
      // контроль решений отождествления 
      void IdentCheck(const TUTrcMsg *pMsg,
                      TProcSituation *pSituation,
                      TSensGenTrcLink **pLink);
      // реализация решений отождествления 
      void SolutionApply(const TUTrcMsg *pMsg,
                         TProcSituation *pSituation,
                         TSensGenTrcLink **pLink);
      // сопровождение 
      void TrcUpdate(const TUTrcMsg *pMsg,
                       /*TMsgProc *pMsgProc,*/
                       TProcSituation *pSituation,
                       TSensGenTrcLink **pLink);

     // простое обновление
     void ReUpdate(const TUTrcMsg *pMsg,
                   TProcSituation *pSituation,
                   int i);

      //формирование выходного решения ТОИ 
      void SolusionRecord(const TUTrcMsg *pMsg,
                          TMsgProc *pMsgProc,
                          TProcSituation *pSituation/*,
                          TSensGenTrcLink **pLink*/);

  //-------------------------------------------------
      //Диспетчер периодического контроля статуса
      void StateTaskChain(bool stateTaskStart, TStateProc *pStateProc,
                          TSensGenTrcLink **pLink,
                          const TSensorDescription *sensorDescription);

      //проверка статуса трассы
      void StateCheck(TStateProc *pStateProc,
                      TSensGenTrcLink **pLink,
                      const TSensorDescription *sensorDescription);

	  // корректировка состояния третичной обработки при стирании информации
	  // о трассах источников, сопровождающих обобщённые трассы
	  int OnSensErasing(bool taskStart, unsigned int genTrcNum);

	  //Сброс обобщённой трассы
      void GenTrcEnd(unsigned int generalTrackNumber);
  //----------------------------------------------------

      void SensTrcAdd(unsigned int generalTrackNumber,
                      unsigned int sensorNumber,
                      unsigned int trackNumber,
                      TSensGenTrcLink **pLink);
      //Вычёркивание трассы источника 
      void SensTrcDelete(unsigned int sensorNumber,
                         unsigned int trackNumber,
                         TSensGenTrcLink **pLink);

      // отведение памяти под дополнительную информацию по трассе источника
      void SensTrcNew(unsigned int sensorNumber,
                      unsigned int trackNumber,
                      TSensGenTrcLink **pLink);

      // сброс трасы источника (освобождение памяти под дополнительную информацию по трассе источника)
      void SensTrcEnd(unsigned int sensorNumber,
                      unsigned int trackNumber,
                      TSensGenTrcLink **pLink);

      // освобождение памяти последовательного анализа
      void SeqentialSolutionDelete(unsigned int sensorNumber,
                                   unsigned int trackNumber,
                                   TSensGenTrcLink **pLink);

      // Определение времени хранения "мёртвой" трассы
      double HoldTime(unsigned int generalTrackNumber);

      // Определение времени хранения трассы с принудит-но стёртыми источниками
      double ErasingHoldTime(unsigned int generalTrackNumber);

	  // Процедура последовательного анализа
      ESeqIdent SeqIdent(const TUTrcMsg *pMsg,
                         TProcSituation *pSituation,
                         TSensGenTrcLink **pLink);

	  TTrcProc(TGeneralTrack &GeneralTrack): Trc(GeneralTrack)
       {}

  }; // class TTrcProc

} // namespace sea

} // namespace PTPV

#endif // _TTRCPROCSEA_H
