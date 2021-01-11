
              //  класс TAir
#ifndef _TAIR_H
#define _TAIR_H

#include "OSInstantiation.h"

#include "AdjustmentCommon.h"

#include <fstream>

#ifdef WINDOWS
#define _WINSOCKAPI_
#include <Windows.h>
#undef _WINSOCKAPI_
#endif

#include "HAirFAL.h"
#include "UZone.h"
#include "TGeneralTrackAir.h"

#include "TTrcProcAir.h"
#include "NUM/Num.h"
#include "TPrognProcAir.h"
#include "TZoneProcAir.h"
#include "TMsgsFormAir.h"
#include "HAir.h"  

#if !(defined BORLAND)
using namespace std;
#endif

namespace PTPV
{

namespace air
{
using namespace COMMON;
using namespace COMMON::_PTPV_;
using namespace COMMON::_ZONE_;

class TAir
{
private:
	
	struct TMsgProc;       // тип по решениям при обработке сообщения
	struct TStateProc;     // тип по решениям при корректировке
	                       //_статуса обобщённой трассы
	// struct TGenTrcMsg;     // тип сообщения с обобщённой трассой

#ifdef WINDOWS
	enum COLOR
	{
	  CYAN			 = FOREGROUND_BLUE | FOREGROUND_GREEN,    // голубой 
	  MAGENTA		 = FOREGROUND_BLUE | FOREGROUND_RED,      // фиолетовый
	  YELLOW		 = FOREGROUND_GREEN | FOREGROUND_RED,     // жёлтый
	  WHITE          = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
	  CYAN_INTENS	 = CYAN | FOREGROUND_INTENSITY,           // ярко-голубой	
	  MAGENTA_INTENS = MAGENTA | FOREGROUND_INTENSITY         // ярко-фиолетовый
	};
	// настройки
	// консоль стандартного вывода
	static HANDLE console;
	// атрибуты стандартного вывода
	static CONSOLE_SCREEN_BUFFER_INFO sattributes0;
#endif
	int printNum;
	static const char *ogpnames[5];
	static const char *classnames[5];
	static const char *lineNames[10];
	ofstream ofile;
	
	// зона характеристик источников
	TSensorDescription SensorDescription [SENS_MAX + 1];
	
	// зона связи трасс источников с обобщённой трассой
	TSensGenTrcLink *Link [SENS_MAX + 1];
	
	TGeneralTrack GeneralTrack;
	
	TTrcProc TrcProc;
    N_U_M::Num num;
	TPrognProc PrognProc;
	TZoneProc ZoneProc;
	TMsgsForm MsgsForm;

	public: struct TRes; private:
	const struct TRes *pres;
		
private:
	// функции загрузки настроечных данных
#ifdef WINDOWS
	static int AssignTextAttributes0();
	static int SetTextAttributes0();
	static int SetTextAttributes(WORD sattributes);
	static int UpTextAttributes(WORD sattributes);
	static int DownTextAttributes(WORD sattributes);
	static int InvertTextAttributes(WORD sattributes);
#endif
	
	/*	// Подготовка к печати информации на экран
	int OInit(); */
	// Подготовка к печати информации в файл
	int OFInit();
	/* // Завершение печати информации на экран
	void OCleanup(); */
	// Завершение печати информации в файл
	void OFCleanup();
	
	// Печать информации по входному сообщению
	static void printTrcMsg(const TUTrcMsg &Msg,ostream &stream);
#ifndef QNX
	// - на экран
	inline static void SPrintTrcMsg(const TUTrcMsg &Msg);
#endif
	// - в файл
	inline void FPrintTrcMsg(const TUTrcMsg &Msg);
    // - на доступные устойства	
	inline void PrintTrcMsg(const TUTrcMsg &Msg);
	
	// Печать информации по выходному сообщению
	static void printGenTrcMsg(const PTPV_TGenTrcMsg &Msg,
	                           ostream &stream);
#ifndef QNX
	// - на экран
	inline static void SPrintGenTrcMsg(const PTPV_TGenTrcMsg &Msg);
#endif
	// - в файл
	inline void FPrintGenTrcMsg(const PTPV_TGenTrcMsg &Msg);
    // - на доступные устойства	
	inline void PrintGenTrcMsg(const PTPV_TGenTrcMsg &Msg);

	// Печать информации по выходному сообщению на периодике
	static void printCheckGenTrcMsg(const PTPV_TGenTrcMsg &Msg,
	                                ostream &stream);
#ifndef QNX
	// - на экран
	inline static void SPrintCheckGenTrcMsg(const PTPV_TGenTrcMsg &Msg);
#endif
	// - в файл
	inline void FPrintCheckGenTrcMsg(const PTPV_TGenTrcMsg &Msg);
    // - на доступные устойства	
	inline void PrintCheckGenTrcMsg(const PTPV_TGenTrcMsg &Msg);

	// Проверка на корректность входного сообщения
	// - о ВО
	/// int MsgValidation(const TUTrcMsg &Msg, double T);
	
	// Пересчёт координатных переменных из СК старой УТ в СК новой.
	void TransformCoords();
	
public:
	
	// текущий результат ТОИ по ВО
	struct TRes
	{
		const TGeneralTrack &GeneralTrack;

#ifdef BORLAND
		TRes (const TGeneralTrack &GenTrack, const TTrackGrp &TrackGrp);
#endif
	};
	typedef void fGiveResult(); 
	
public:
	TAir(TZone monitoredZones[ZONE_MAX]);
	~TAir();
	
	// Приём сообщения о ВО
	const TAir::TRes &GetMsg(const TUTrcMsg &Msg, double T,
	                  TMsgFormSet *pmsgFormSet, PTPV_TGenTrcMsg *pGenTrcMsg);
	
	// Корректировка статуса трассы
	const TAir::TRes &TrcStateCheck(double T, TMsgFormSet *pmsgFormSet,
	                  PTPV_TGenTrcMsg *pGenTrcMsg, fGiveResult *fpResult);

	operator const TRes &() const;

	// Печать информации по отработке ТОИ в файл
	TAir &operator <(const char *const Msg); 
	TAir &operator <(const char symbol);
	TAir &operator <(const int number);
	TAir &operator <(const double value);
	TAir &operator <(const TUTrcMsg &TrcMsg);
	TAir &operator <(const PTPV_TGenTrcMsg &GenTrcMsg);
#ifndef QNX
	// Печать информации по отработке ТОИ на экран и в файл
	TAir &operator <=(const char *const pMsg); 	
	TAir &operator <=(const char symbol);
	TAir &operator <=(const int number);
	TAir &operator <=(const double value);
#endif
	// Печать информации по отработке ТОИ на те устойства, куда это возможно
	TAir &operator <<(const char *const pMsg); 	
	TAir &operator <<(const char symbol);
	TAir &operator <<(const int number);
	TAir &operator <<(const double value);
	
}; // class TAir

} // namespace air

} // namespace PTPV

#endif // _TAIR_H
