
              //  класс TSea
#ifndef _TSEA_H
#define _TSEA_H

// если определено, то вызов ТОИ по МО/НО из модели (без ПС ОВП)
// #define USING_SEA_BY_MODEL 1

#include "AdjustmentCommon.h"

#include "HSeaFAL.h"
#include "UZone.h"
#include "TGeneralTrackSea.h"

#include "TTrcProcSea.h"
#include "NUM/DispatcherNUM.h"
#include "TPrognProcSea.h"
#include "TZoneProcSea.h"
#include "TMsgsFormSea.h"
#include "HSea.h"

namespace PTPV
{

namespace sea
{
using namespace COMMON;
using namespace COMMON::_PTPV_;

class TSea
{
private:
	
	struct TMsgProc;      // тип по решениям при обратотке сообщения
	struct TStateProc;    // тип по решениям при корректировке
	                      //_статуса обобщённой трассы
	struct TGenTrcMsg;    // тип сообщения с обобщённой трассой
	
	// зона характеристик источников
	TSensorDescription SensorDescription [SENS_MAX + 1];
	
	// зона связи трасс источников с обобщённой трассой
	TSensGenTrcLink *Link [SENS_MAX + 1];
	
	TCountKeep CountKeep;
	
	TGeneralTrack GeneralTrack;
	
	TTrcProc TrcProc;
	N_U_M::DispatcherNUM dispatcherNUM;
	TPrognProc PrognProc;
	TZoneProc ZoneProc;
	TMsgsForm MsgsForm;

	public: struct TRes; private:
	const struct TRes *pres;
	
private:
	// Формирование заголовка PTPV_Msg_Sea
	void FormTrcMsgHdr(PTPV_TGenTrcMsg* pGenTrcMsg, double currentT);
	
	// Формирование выходного сообщения
	void FormGenTrcMsg(int i, const TMsgProc* pMsgProc,
	                   PTPV_TGenTrcMsg* pGenTrcMsg);
	
	// Проверка на корректность входного сообщения
	// - о НПО
	int MsgValidation(const TUTrcMsg &Msg, double T) {return 0;/*тимч.*/};

	// Процедура приведения объекта к начальному состоянию.    
	void Init();
 
public:
	
	// текущий результат ТОИ по НВО/НО
	struct TRes
	{
		const TGeneralTrack &GeneralTrack;

#ifdef BORLAND
		TRes (const TGeneralTrack &GenTrack);
#endif
	};
	typedef void fGiveResult
	             (PTPV_TGenTrcMsg* pGenTrcMsg, void *pobject); 

public:
	TSea(TZone monitoredZones[ZONE_MAX]);
	~TSea();
	
	// Приём сообщения о НВО либо НО
	int GetMsg(const TUTrcMsg &Msg, double T,
	           TMsgFormSet *pmsgFormSet, PTPV_TGenTrcMsg pGenTrcMsg[2]);

	// Корректировка статуса трассы
	const TRes &TrcStateCheck(double currentT,
	                          fGiveResult *fpResult = 0, void *pobject = 0);
		
	operator const TRes &() const;
	
}; // class TSea

} // namespace sea

} // namespace PTPV

#endif // _TSEA_H
