
              //  HSea
#ifndef _HSEA_H
#define _HSEA_H

#include "AdjustmentCommon.h"

#include "ESea.h"
#include "DefSea.h"

namespace PTPV
{

namespace sea
{
using namespace COMMON;
using namespace COMMON::_PTPV_;

	// Характеристика источника
	struct TSensorDescription 
	{
		unsigned char    type;               // тип 
		unsigned int     trackCount;         // количество тpасс
		unsigned int     maxTrackNumber;     // максимальный номер тpассы
		double           dataTemp;          // темп выдачи данных  
		}; // struct TSensorDescription
	
	// Дополнительная информация по трассе источника  в зоне связи
	// трасс источников с обобщённой трассой
	struct TSensTrcData
	{
		// информация источника
		double tLastMsg;        // время прихода последнего сообщения 
		double tIndNumUpdate;   // время прихода последнего сообщения об
		                        // индивидуальном номере
		double t;               // время, которому соответствуют координаты ВО
		                        //       (в шкале UTC)
		float  x;               // координата X
		float  y;               // координата Y
		float  h;               // радиолокационная выоста
		float  hBar;            // барометрическая высота
		float  trustXY;         // 1/2 доверительного интервала по
		                        // координатам X, Y
		float  trustH;          // 1/2 доверительного интервала по
		                        // радиолокационной высоте Н
		float  v;               // скорость
		float  psi ;            // курс полета
		long   indNum;          // индивидуальный номер
		long   uniNum;          // единый номер
		EUOGP   OGP;            // ОГП
		EUSOS   SOS;            // признак вида бедствия
		EUYesNo manevr;         // признак наличия маневра (YES - есть маневр)
		unsigned char quant;    // количественный состав (1-7)
		unsigned int  attackStateFA      : 1,    // признак воздействия ИА
		              attackStateSAM     : 1,    // признак воздействия ЗРВ
		              attackStateReserve : 1;    // признак воздействия - резерв
		
		unsigned int  xyUpdate           : 1,    // признак обновления по XY
		              hUpdate            : 1,    // признак обновления по h
		              hBarUpdate         : 1,    // признак обновления по hBar
		              OGPUpdate          : 1,    // признак обновления по OGP
		              manevrUpdate       : 1,    // признак обновления по манёвру
		              quantUpdate        : 1,    // признак обновления
		                                         // по количественному составу
		              attackStateUpdate  : 1;    // признак обновления по
                                                 // воздействию
		unsigned char mismatXYCount;         // счётчик несовпадений по X, Y
	}; // struct TSensTrcData
	
    /*
	// Информация последовательного анализа
	struct TSeqentialSolution
	{
		unsigned int  num;       // номер отобранной обобщённой трассы
		unsigned char step;
		double MIN;
    };  // struct TSeqentialSolution
	*/
	
	// Информация последовательного анализа
	struct TSeqSolution
	{
        // информация последовательного анализа для трасс
        double MIN;
        unsigned int  num;       // номер отобранной обобщённой трассы
		unsigned char selectTrcQuant,   // кол-во отобранных для
		                                // последовательного анализа трасс
		              step;             // номер шага последовательного анализа
		
		// подструктура характеристик отобранной для
		// последовательного анализа трассы
		struct TCandidateTrc
		{
			double  crit;               // значение критерия отождествления
			double  fuzzyMinExtreme;    // значение ф-ции принадлежности 
			double  fuzzyMin;           // значение ф-ции принадлежности 
			double  fuzzyMax;           // значение ф-ции принадлежности 
			double  fuzzyMaxExtreme;    // значение ф-ции принадлежности
			int     genTrcNum;          // номер отобранной для
			                            // последовательного анализа трассы
		} CandidateTrc [SEQ_CANDIDATE_MAX];
	}; // struct TSeqSolution
	
	// Связка трассы источника с обобщённой трассой
	struct TSensGenTrcLink
	{
        unsigned int genTrc; // номер обобщённой трассы
		EIdentState  identState; // состояние отождествления трассы 
                                   //  0 - нет трассы
                                   //  1 - приход первого донесения о трассе 
                                   //  2 - трасса на последовательном анализе
                                   //  3 - трасса отождествлена безусловно
                                   //  4 - условное отождествление по ОГП
                                   //  5 - условное отождествление по H
                                   //  6 - условное отождествление по ОГП и H
        TSensTrcData *Data;           // указатель на  информацию источника
        TSeqSolution *SeqSolution;  // указатель на  информацию
		                            // последовательного анализа
	}; // struct TSensGenTrcLink
	
	// Счётчики посылаемых сообщений
	struct TCountKeep
	{
		unsigned int   PTPV_Msg_Sea;
	}; // // счётчики посылаемых сообщений
	
	// зона решений при обработке сообщения
	struct TMsgProc
	{
		unsigned char trkState;    // признак сопрoвoждения:
		                                // 1  новый ВО,
		                                // 2  спровождаемый ВО,
		                                // 3  сбрoс ВО;
		unsigned char error;       // ошибка при обработке сообщения
		
		struct TUpdate
		{
			unsigned char newTrc;
			unsigned int  trcNum;
			unsigned char sensAdd;
			unsigned char sensDelete;     
			unsigned char trcUpdate;
			unsigned char xyUpdate;
			unsigned char hUpdate;
			unsigned char OGPUpdate;
			unsigned char OGPChange;
		} Update[2];
	}; // struct TMsgProc
	
	// Зона решений при корректировке статуса обобщённой трассы
	struct TStateProc
	{
		double        currentT;                   // текущее время
		unsigned int  genTrcNum;                  // номер обобщённой трассы
		long          sensTrcDelete[SENS_MAX+1];  // массив сбрасываемых
		                                          // источников
		unsigned char sensTrcDrop;                // сброс источника(ов)
		unsigned char genTrcDrop;                 // сброс обобщённой трассы
	}; // struct TStateProc
	
} // namespace sea

} // namespace PTPV

#endif // _HSEA_H
