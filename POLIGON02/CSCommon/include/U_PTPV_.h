﻿/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
@Copyright (c)          : АО "РКС"
@Имя файла              : U_PTPV_.h
@Описание               : Определения перечислений и типов унифицированных
                          структур данных для обмена информацией ПК третичной
                          обработки с его источниками и потребителями.
@Замечания              : Общий заголовочный файл ПК КВМНО.
@Автор                  : Самсон С. Ю., Сорокин А. В., Дронова Л. В.
@Дата                   : 21.05.2019
@Инструментальная среда : Microsoft Visual Studio Express 2012
@Дополнительно          : Передаётся разработчикам всех ПК и ПКп.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef U_PTPV__H
#define U_PTPV__H

#include "UGeneral.h"
#include "U.h"

namespace COMMON
{

namespace _PTPV_
{

//-----------------------------------
// Тип информации ДА-НЕТ.
enum EUYesNo
{
   EU_NO  = 0,    // Нет
   EU_YES = 1     // Да
}; // enum EUYesNo

//-----------------------------------
// Признак состояния сопровождения.
enum EUTrcState
{
   EU_TS_NEW = 1,    // Новая
   EU_TS_TRK = 2,    // Сопровождаемая
   EU_TS_END = 3     // Сбрасываемая
}; // enum EUTrcState


#pragma pack(push, 4)

// ---------------------------------------------------------------------------
/**
 * Трассовая информация объекта (ВО, МО, НО) от источника.
 */

struct TUTrcMsg : public TUMsgHdr
{
	unsigned char sensNum;     // Номер источника информации (1-4)
	int           trcNum;      // Номер трассы в системе нумерации источника
	EUYesNo       imitObj;     // Признак имитационного объекта
	                           //_(EU_YES - имитационная трасса,
	                           //_а EU_NO - реальная трасса)
	EUTrcState    trcState;    // Признак состояния сопровождения трассы
	
	// кинематические характеристики объекта:
	double t;          // Время, которому соответствуют координаты
	                   //_объекта, высота и другие признаки    (в шкале UTC)
	float  x;          // Координата X
	float  y;          // Координата Y
	float  h;          // Высота (глубина)
	float  hBar;       // Барометрическая высота
	float  trustXY;    // 1/2 доверительного интервала по координатам X, Y
	float  trustH;     // 1/2 доверительного интервала по высоте .h
	float  vX;         // Сoставляющая скoрoсти по координате X
	float  vY;         // Сoставляющая скoрoсти по координате Y
	float  vH;         // Сoставляющая скoрoсти по высоте .h
	float  v;          // Модуль скорости (по плоскостным координатам X, Y)
	float  psi;        // Курс движения
	float  aX;         // Сoставляющая ускорения по координате X
	float  aY;         // Сoставляющая ускорения по координате Y
	float  aH;         // Сoставляющая ускорения по высоте .h
	
 	EUYesNo       manevr;      // Признак наличия манёвра (EU_YES - есть манёвр)
	unsigned char quant;       // Количественный состав (1-15)
	EUSensType    sensType;    // Тип источника информации
	
	// информация САЗО-СГО:
	EUOGP     OGP;        // ОГП
	EUReqLine reqLine;    // Линия запроса
	EUSOS     SOS;        // Признак вида бедствия
	long      indNum;     // Индивидуальный номер ВО

	// типовые характеристики объекта:
	unsigned char objClass;         // Категория объекта: воздушный,
	                                //_морской, наземный, находящийся
	                                //_на поверхности (из EUObjClass)
	unsigned char TO;               // Тип воздушного объекта (СИНТВО)
	                                //_(из EUTVO, EUTMO, или EUTNO)
	unsigned char seaObjType;       // Тип морского объекта (словарь типов)
	unsigned char seaObjName[9];    // Имя морского объекта
	unsigned char seaIndNum[9];     // Бортовой номер морского объекта
	
	unsigned char flyViolatKind;    // Вид нарушения режима полёта
	unsigned char requestNum[7];    // Номер заявочного самолёта
	unsigned char IO;               // Индекс воздушного объекта (СИНТВО)
	                                //_(из EUIVO)
	long          uniNum;           // Единый номер воздушного объекта
	
	// информация об обновлении характеристик объекта:
	//           Признаки обновления update
	unsigned int                    : 0,  // Обеспечение выравнивания
	                                      //_последующего набора битовых полей
	                                      //_по границе слова
	             xyUpdate           : 1,  // Признак обновления по X и Y
	             hUpdate            : 1,  // Признак обновления по высоте .h
	             hBarUpdate         : 1,  // Признак обновления по высоте .hBar
	             OGPUpdate          : 1,  // Признак обновления по ОГП
	             manevrUpdate       : 1,  // Признак обновления по манёвру
	             quantUpdate        : 1,  // Признак обновления
	                                      //_по количественному составу
	                                : 0;  // Обеспечение выравнивания
	                                      //_последующего поля по границе слова
}; // struct TUTrcMsg


// ---------------------------------------------------------------------------
/**
 * Обобщённая трассовая информация объекта (ВО, МО, НО)
 * по результатам третичной обработки.
 */

struct PTPV_TGenTrc
{
	EUYesNo imitObj;    // Признак имитационного объекта
	                    //_(EU_YES - имитационная трасса,
	                    //_а EU_NO - реальная трасса)
	
	// таймерные информативные признаки    (в шкале UTC):
	double tStart;           // Время образования обобщённой тpассы
	double tXYUpdate;        // Время реального обновления координат X и Y
	double tHUpdate;         // Вpемя реального обновления высоты
	double tHBarUpdate;      // Вpемя реального обновления
	                         //_барометрической высоты
	double tOGPUpdate;       // Вpемя обновления ОГП
	double tIndNumUpdate;    // Вpемя обновления индивидуального номера
	
	// кинематические характеристики объекта:
	float x;          // Координата X
	float y;          // Координата Y
	float h;          // Высoта (глубина)
	float hBar;       // Барометрическая высoта
	float trustXY;    // 1/2 доверительного интервала по координатам X, Y
	float trustH;     // 1/2 доверительного интервала по высоте
	float vX;         // Сoставляющая скoрoсти по X
	float vY;         // Сoставляющая скoрoсти по Y
	float v;          // Модуль скоpости (пo плоскостным координатам X, Y)
	float psi;        // Курс движения
	
 	EUYesNo       manevr;      // Признак наличия манёвра (EU_YES - есть манёвр)
	unsigned char quant;       // Количественный состав (1-15)
	
	unsigned char sensCount;                // Количество источников,
	                                        //_сопpовождающих данную
	                                        //_обобщённую трассу
	int           sensTrcNum [SENS_MAX];    // Массив номеров трасс от
	                                        //_источников сопровождения,
	                                        //_индекс элемента массива
	                                        //_соответствует номеру источника
	
	// информация САЗО-СГО:
	EUOGP     OGP;        // ОГП
	EUReqLine reqLine;    // Линия запроса
	EUSOS     SOS;        // Признак вида бедствия
	long      indNum;     // Индивидуальный номер ВО по системам
	                      //_УВД, "Пароль", "Пароль-Радуга"
	long indNumRBS;       // Индивидуальный номер ВО по RBS
	long indNumMK;        // Индивидуальный номер ВО по Mk-XA/Mk-XII
	
	// типовые характеристики объекта:
	unsigned char objClass;         // Категория объекта: воздушный,
	                                //_надводный, наземный, находящийся
	                                //_на поверхности (из EUObjClass)
	unsigned char TO;               // Тип воздушного объекта (СИНТВО)
	                                //_(из EUTVO, EUTMO, или EUTNO)
	unsigned char seaObjType;       // Тип морского объекта (словарь типов)
	unsigned char seaObjName[9];    // Имя морского объекта
	unsigned char seaIndNum[9];     // Бортовой номер морского объекта
	
	unsigned char flyViolatKind;    // Вид нарушения режима полёта
	unsigned char requestNum[7];    // Номер заявочного самолёта
	unsigned char IO;               // Индекс воздушного объекта (СИНТВО)
	                                //_(из EUIVO)
	long          uniNum;           // Единый номер воздушного объекта
	
	bool zones [ZONE_MAX];    // Принадлежность объекта зоне
	struct
	{   //    прогнозируемое местоположение объекта
		float x;                   // Координата X
		float y;                   // Координата Y
		bool  zones [ZONE_MAX];    // Принадлежность объекта зоне
	}    progn;               // Прогноз на заданное время
}; // struct PTPV_TGenTrc


// ---------------------------------------------------------------------------
/**
 * Обобщённая трассовая информация объекта (ВО, МО, НО) потребителям ПК ТОИ.
 */

struct PTPV_TGenTrcMsg : public TUMsgHdr
{
	int          genTrcNum;    // Нoмep обобщённой трассы
	EUTrcState   trcState;     // Признак состояния сопрoвoждения трассы
	PTPV_TGenTrc trc;          // Сведения обобщённой трассы объекта
	                           //_по результатам третичной обработки
	
	// свод изменений в обобщённой трассе объекта по результатам ТОИ:
	EUYesNo      sensAdd;            // Добавление источника информации
	                                 //_(EU_YES - добавлен источник)
	EUYesNo      sensDelete;         // Удаление источника информации
	                                 //_(EU_YES - удалён источник)
	//           Обновления (update) признаков обобщённой трассы
	unsigned int               : 0,  // Обеспечение выравнивания
	                                 //_последующего набора битовых полей
	                                 //_по границе слова
		         xyUpdate      : 1,  // Обновление координат X и Y
	             hUpdate       : 1,  // Обновление высоты .trc.h или .trc.hBar
	             ogpUpdate     : 1,  // Обновление ОГП
		                       : 0;  // Обеспечение выравнивания
	                                 //_последующего поля по границе слова
}; // struct PTPV_TGenTrcMsg

#pragma pack(pop)

} // namespace _PTPV_

} // namespace COMMON

#endif /* U_PTPV__H */
