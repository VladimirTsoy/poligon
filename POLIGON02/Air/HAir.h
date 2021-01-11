/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
@Copyright (c)  		       :
       Центр МНИИПА ОАО "ГСКБ "Алмаз-Антей"
@Имя файла    		       :
       HAir.h
@Описание  		       :
       структуры функциональной задачи обработки информации по ВО
@Замечания    		       :
@Автор 			:
      Самсон С. Ю.
@Дата   			:
      22.07.2011
@Инструментальная среда	       :
      Microsoft Visual C++9.0.
@Дополнительно   		:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

              //  HAir
#ifndef _HAIR_H
#define _HAIR_H

#include "AdjustmentCommon.h"

#include "EAir.h"
#include "DefAir.h"

namespace PTPV
{

namespace air
{
using namespace COMMON;
using namespace _PTPV_;

	// Характеристика источника
	struct TSensorDescription 
	{
		unsigned char    type;               // тип 
		unsigned int     trackCount;         // количество тpасс
		unsigned int     maxTrackNumber;     // максимальный номер тpассы
		unsigned int     genTrcNum;          // номер тpассы носителя
		double           dataTemp;           // темп выдачи данных
        int              rank;               // ранг источника
        bool             ph;                 // ПХ
        int              typeNum;            // тип источника
	};
	
	// Дополнительная информация по трассе источника в зоне связи
	// трасс источников с обобщённой трассой
	struct TSensTrcData
	{
		// информация источника
		double tLastMsg;        // время прихода последнего сообщения 
		double tIndNumUpdate;   // время прихода последнего сообщения об
		                        // индивидуальном номере
		double t;               // время, которому соответствуют координаты ВО
		                        //       (в шкале UTC)
		float  x;               // координата X  // предусмотреть прзнк. обновл. 
		float  y;               // координата Y  // для случая командню отожд-я.
		float  h;               // радиолокационная высота
		float  hBar;            // барометрическая высота
		float  trustXY;         // 1/2 доверительного интервала по
		                        // координатам X, Y
		float  trustH;          // 1/2 доверительного интервала по
		                        // радиолокационной высоте h
		float  v;               // скорость
		float  psi;             // курс движения
		long   indNum;          // индивидуальный номер
		long   uniNum;          // единый номер
		EUOGP   OGP;            // ОГП
		EUSOS   SOS;            // признак вида бедствия
		EUYesNo manevr;         // признак наличия маневра (YES - есть маневр)
		unsigned char quant;         // количественный состав (1-7)
		
		unsigned int xyUpdate           : 1,    // признак обновления по X и Y
		             hUpdate            : 1,    // признак обновления по .h
		             hBarUpdate         : 1,    // признак обновления по .hBar
		             OGPUpdate          : 1,    // признак обновления по ОГП
		             manevrUpdate       : 1,    // признак обновления по манёвру
		             quantUpdate        : 1;    // признак обновления по
		                                        // количественному составу
		unsigned char mismatXYCount;        // счётчик несовпадений по X, Y
		int IO;
		int TO;
	}; // struct TSensTrcData
	
	// Информация последовательного анализа
	struct TSeqSolution
	{
		int selectTrcQuant,   // кол-во отобранных для
		                      // последовательного анализа трасс
		    step;             //  номер шага последовательного анализа
    
		// подструктура характеристик отобранной для
		// последовательного анализа трассы
		struct TCandidateTrc
		{
			double   crit;               // значение критерия отождествления
			double   fuzzyMinExtreme;    // значение ф-ции принадлежности 
			double   fuzzyMin;           // значение ф-ции принадлежности 
			double   fuzzyMax;           // значение ф-ции принадлежности 
			double   fuzzyMaxExtreme;    // значение ф-ции принадлежности
			int      genTrcNum;          // номер отобранной для
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
		TSensTrcData *Data;           // указатель на информацию источника
		TSeqSolution *SeqSolution;  // указатель на информацию
		                            // последовательного анализа
	}; // struct TSensGenTrcLink
	
	// Счётчики посылаемых сообщений
	struct TCountKeep
	{
		double       tPeriod;
		unsigned int PTPV_Msg_Air;
	}; // struct TCountKeep

	// Зона решений при обработке сообщения
	struct TMsgProc
	{
		unsigned char trkState;    // признак сопрoвoждения:
		                                // 1  новый ВО,
		                                // 2  спровождаемый ВО,
		                                // 3  сбрoс ВО;
		unsigned char error;       // ошибка при обработке сообщения
		                           // "канальная цель" по несуществующей трассе
		
		int NumSensorPH[SENS_MAX]; //номера источников, на которые следует передать ПХ
		
		struct TUpdate
		{
			unsigned char newTrc;
			/*unsigned*/ int trcNum;
			unsigned char sensAdd;
			unsigned char sensDelete;     
			unsigned char trcUpdate;
			unsigned char xyUpdate;
			unsigned char hUpdate;
			unsigned char OGPUpdate;
			unsigned char OGPChange;
		} Update[2];
		 
	}; // struct TMsgProc
		
		// зона решений при корректировке статуса обобщённой трассы
		struct TStateProc
		{
			// double        currentT;                   // текущее время
			/*unsigned int*/short genTrcNum;          // номер обобщённой трассы
			long          sensTrcDelete[SENS_MAX+1];  // массив сбрасываемых
			                                          // источников
			unsigned char sensTrcDrop;                // сброс источника(ов)
			unsigned char genTrcDrop;                 // сброс обобщённой трассы
		}; // struct TStateProc
	
} // namespace air

} // namespace PTPV

#endif // _HAIR_H
