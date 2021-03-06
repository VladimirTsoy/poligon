﻿/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
@Copyright (c)          : ОАО "РКС"
@Имя файла              : IMIT_.h
@Описание               : Определения констант и типов структур данных
                          для передачи информации КФП IMIT его потребителям.
@Замечания              : Общий заголовочный файл ФПО БИУС.
                          Если используется стандарт C++, стандартная библиотека
                                                  которого не содержит заголовочный файл <stdint.h>,
                                                  должен быть определён макрос __OLDSTD.
@Автор                  : ?
@Дата                   : ?.?.2015
@Инструментальная среда : Microsoft Visual C++ 2008
@Дополнительно          : Передаётся разработчикам всех КФП.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef _IMIT__H
#define _IMIT__H

#include "U.h"

namespace COMMON
{

namespace _IMIT_
{

//------------------------------
//  Максимальное количество эталонов (было = 100), увеличенное на 1
enum
{
   TRACK_MAX = 221
};

//------------------------------
//  Количество типов источников, увеличенное на 1
enum
{
   SENS_CHAR_MAX = 5
};


// ---------------------------------------------------------------------------
//
// Зона эталонов контрольных задач
 //

struct TObjectContr //Link
{        //зона параметров эталона
    float         tStart;                  //[c] Время начала имитации объекта  [TH]
    float         tFinish;                 //[c] Время окончания имитации объекта [TK]
    float         x;                       //[м] коорд опорная объекта  [XO]
    float         y;                       //[м] коорд опорная объекта  [YO]
    float         h;                       //[м] высота опорная объекта  [VO]
    float         v;                       //[м/с]скорость объекта
    float         vh;                       //[м/с]скорость по высоте объекта
    float         psi;                     //[град] курс объекта
    unsigned char  countManevr;             //количество маневров     [KM]
    EUObjClass     ObjClass;               /// Класс объекта
                                               //UOC_AIR     = 1,     Воздушный (AIR)
                                               //  UOC_SEA     = 2,     Надводный (SEA)
                                               // UOC_GROUND  = 3,     Наземный (GROUND)
    EUOGP          OGP;                     // ОГП
    int          IO;                     // Не опознан,=3- воздушный противник
    int          TO;                     // типа воздушного объекта.=8-ГЗЛА, =10-БР, =11-КР, =14-СА
    bool        trackBZ;                 // формуляр занят  (YES-занят) [ZF]
    struct TManevr
    {        //зона маневров эталона
      float       tStart;                  //[c] Время начала маневра
      float       tFinish;                 //[c] Время окончания маневра
      float       a;                       //[м/с2] ускорение
      float       vh;                      //[м/с]скорость изменения высоты
      float       r;                       //[м] радиус разворота
    } Manevr[10] ;                             //
};
//------------------------------------------------------------------------------------------------//

// ---------------------------------------------------------------------------
/////
////  Характетистики ИИ по типу [TOI]
////

struct TCharSens
{
    float          hMax,                    //[м] максимальная высота отбора
                   hMin,                    //[м] минимальная высота отбора
                   rMax,                   //[м] радиус зоны отбора         [R]
                   rMin,                   //[м] радиус зоны отбора         [R]
                   trustXY,                //доверительный интервал
                   trustH;                  //доверительный интервал
     unsigned int   maxCountTrc;             // количество трасс                  [P]

};

// ---------------------------------------------------------------------------
//
// Динамические характеристики
//

struct TDinChar
{
    bool        regimeImit;              //включение режима имитации,YES- включена имитация
    bool        realTime;                //режим реального времени (YES-включен)
    bool        zoneView;                //расширение зоны видимости
    unsigned int   countRecord,             // количество занятых формуляров      [KZF]
                   countLibertyRecord,      // количество свободных формуляров      [KSF]
                   countContr,              //количество эталонов в контрольной задаче
                   countMessage;           //количество сообщений на выдачу
    unsigned char  numberContr,             //номер контрольной задачи
                   objectContr;             //1-включение режима контрольной задачи
};

// ---------------------------------------------------------------------------
//
// Общедоступные параметры эталона (IZ01)
//

struct TPubEtalon
{
    float          v;                      ///[м] Скорость объекта
    float          vx;                     ///[м] Составляющая вектора скорости
    float          vy;                     ///[м/с] Составляющая вектора скорости
    float          vh;                     ///[м/с] Скорость изменения высоты
    float          ax;                     ///[м/с2]Ускорение
    float          ay;                     ///[м/с2] Ускорение
    float          ah;                     ///[м/с2] Ускорение
    float          psi;                    /// Курс объекта
    float          x;                      ///[м] Коорд объекта
    float          y;                      ///[м] Коорд объекта
    float          h;                      ///[м] Высота объекта
    int            trcNumSens[SENS_MAX];   /// Массив номеров трасс источников,
                                            /// сопровождающих данный эталон, индекс
                                            /// элемента массива соответствует номеру источника [UIC+NT]
    float          trustXY;                /// Доверительный интервал по координатам
    EUObjClass     ObjClass;               /// Класс объекта
                                               //UOC_AIR     = 1,     Воздушный (AIR)
                                               //  UOC_SEA     = 2,     Надводный (SEA)
                                               // UOC_GROUND  = 3,     Наземный (GROUND)
    int          IO;                    // Не опознан,=3- воздушный противник
    int          TO;                      // типа воздушного объекта.=8-ГЗЛА, =10-БР, =11-КР, =14-СА
    EUOGP           OGP;                    // ОГП
    bool         manevr;                 /// Признак наличия маневра (YES - есть маневр) [EUYesNo]
    bool         visual;                 /// Признак необходимости отображать информацию (YES - отображать)  [EUYesNo]

};

// ---------------------------------------------------------------------------
//
// Заголовок для TPubEtalon (выходное сообщение)
//

struct TMsgTrc
{
    unsigned int    numEt;                      //[номер эталона
    unsigned int    trcNum;                      //номер трассы источника
    double          currentT;                       //текущее время
    short int       numSens;                      //номер ИИ
    unsigned char   sensChar;                 // тип ИИ
    unsigned char   copr;                 // тип сопровождения
    float           trustXY;    // 1/2 доверительного интервала по координатам X, Y
    float           trustH;     // 1/2 доверительного интервала по радиолокационной

};

// ---------------------------------------------------------------------------
//
// Местоположение ИИ
//

struct TSensSite
{
    float           x,                      //[м] коорд источника
                    y;                      //[м] коорд источника
     unsigned char sensChar;                 // тип источника           [TOI]
};

} // namespace _IMIT_

} // namespace COMMON

#endif /* _IMIT__H */
