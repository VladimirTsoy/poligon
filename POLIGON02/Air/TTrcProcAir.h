
              // класс TTrcProc

#ifndef _TTRCPROCAIR_H
#define _TTRCPROCAIR_H

#include "AdjustmentCommon.h"
#include "HAir.h"
#include "TGeneralTrackAir.h"

#include "DefAir.h"
#include "EAir.h"

namespace PTPV
{

namespace air
{
using namespace COMMON::_PTPV_;
	
extern const TGenTrcS CGenTrcS0;  // нулевой формуляр зоны обобщённых трасс 

class TTrcProc
{
private:
	
	struct TProcSituation;    // тип состояния решений по входному сообщению
	
	TSensorDescription *SensorDescription;
	TSensGenTrcLink **Link;
	TGeneralTrack &Trc;
	
private:

	// Анализ ситуации по входному сообщению
	void MsgCheck(const TUTrcMsg &Msg, double T,
	              TProcSituation *pSituation,
	              TSensGenTrcLink **pLink);
	
	// Отождествление
	void Ident(const TUTrcMsg &Msg,
	           TProcSituation *pSituation,
	           TSensGenTrcLink **pLink);
	
	// Отбор обобщённых трасс по координатам
	void CrdSelect(const TUTrcMsg &Msg,
	               TProcSituation *pSituation);
	
	// Отбор обобщённых трасс по индивидуальному номеру
	void IndNumSelect(const TUTrcMsg &Msg,
	                  TProcSituation *pSituation,
	                  TSensGenTrcLink **pLink);
	
	// Переотождествление
	void ReIdentIndNum(const TUTrcMsg &Msg,
	                   TProcSituation *pSituation,
	                   TSensGenTrcLink **pLink);
	
	// Переотождествление
	void ReIdentCrd(const TUTrcMsg &Msg,
	                TProcSituation *pSituation,
	                TSensGenTrcLink **pLink);
	
	// Переотождествление
	void ReIdentSens(const TUTrcMsg &Msg,
	                 TProcSituation *pSituation,
	                 TSensGenTrcLink **pLink);
	
	// Контроль решений отождествления 
	void IdentCheck(const TUTrcMsg &Msg,
	                TProcSituation *pSituation,
	                TSensGenTrcLink **pLink);

	// Реализация решений отождествления 
	void SolutionApply(const TUTrcMsg &Msg,
	                   TProcSituation *pSituation,
	                   TSensGenTrcLink **pLink);

	// Сопровождение 
	void TrcUpdate(const TUTrcMsg &Msg,
	               /* TMsgProc* pMsgProc, */
	               TProcSituation *pSituation,
	               TSensGenTrcLink **pLink);
	
	// Формирование выходного решения ТОИ 
	void SolusionRecord(const TUTrcMsg &Msg,
	                    TMsgProc* pMsgProc,
	                    TProcSituation *pSituation,
	                    TSensGenTrcLink **pLink);
	
	//-------------------------------------------------
	// Проверка статуса трассы
	void StateCheck(double T, TStateProc *pStateProc,
	                TSensGenTrcLink **pLink,
	                const TSensorDescription *sensorDescription);

	// Сброс обобщённой трассы
	void GenTrcEnd(unsigned int generalTrackNumber);
	//----------------------------------------------------
	
	// Вписывание трассы источника в обобщённую трассу
	void SensTrcAdd(unsigned int generalTrackNumber,
	                unsigned int sensorNumber,
	                unsigned int trackNumber,
	                unsigned char mobTrack,
	                TSensGenTrcLink **pLink);
	// Вычёркивание трассы источника 
	void SensTrcDelete(unsigned int sensorNumber,
	                   unsigned int trackNumber,
	                   unsigned char mobTrack,
	                   TSensGenTrcLink **pLink);
	
	// Отведение памяти под дополнительную информацию по трассе источника
	void SensTrcNew(unsigned int sensorNumber,
	                unsigned int trackNumber,
	                TSensGenTrcLink **pLink);
	
	// Сброс трасы источника (освобождение памяти под дополнительную информацию
	// по трассе источника)
	void SensTrcEnd(unsigned int sensorNumber,
	                unsigned int trackNumber,
	                TSensGenTrcLink **pLink);
	
	// Освобождение памяти последовательного анализа
	void SeqentialSolutionDelete(unsigned int sensorNumber,
	                             unsigned int trackNumber,
	                             TSensGenTrcLink **pLink);
	
	// Определение времени хранения "мёртвой" трассы
	double HoldTime(unsigned int generalTrackNumber);
	
	// Процедура последовательного анализа
	ESeqIdent SeqIdent(const TUTrcMsg &Msg,
	                   TProcSituation *pSituation,
	                   TSensGenTrcLink **pLink);
	
	// Обновление координат заменой
	void ChangeUpdate(const TUTrcMsg &Msg,
	                  TProcSituation *pSituation,
	                  unsigned int genTrcNum);

	// Обновление координат фильтрацией
	void FilterUpdate(const TUTrcMsg &Msg,
	                  TProcSituation *pSituation,
	                  TSensGenTrcLink **pLink,
	                  unsigned int genTrcNum);
	
	// Обновление высоты
	void HUpdate(const TUTrcMsg &Msg,
	             TProcSituation *pSituation,
	             unsigned int genTrcNum,
	             int i);
	
	// Обновление признаков
	void CharUpdate(const TUTrcMsg &Msg,
	                TProcSituation *pSituation,
	                TSensGenTrcLink **pLink,
	                unsigned int genTrcNum,
	                int i/*unsigned char sensAddGenTrc*/);
		
public:

	//===================================================
	TTrcProc(TGeneralTrack &GeneralTrack, TSensGenTrcLink **pLink,
	         TSensorDescription *pSensorDescription);
	
	//===================================================
	// Диспетчер задач
	void MsgTaskChain(const TUTrcMsg &Msg, double T, TMsgProc *pMsgProc);
	
	//===================================================
	// Диспетчер периодического контроля статуса
	void StateTaskChain(bool stateTaskStart, double T, TStateProc *pStateProc);
	
}; // class TTrcProc
	
} // namespace air

} // namespace PTPV

#endif // _TTRCPROCAIR_H
