﻿/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
@Copyright (c)          : ОАО "РКС"
@Имя файла              : HImit.h
@Описание               : Определения типов структур данных реализации ИМ.
@Замечания              : Общий заголовочный файл ИМ.
@Автор                  : ?
@Дата                   : ?.?.2015
@Инструментальная среда : Microsoft Visual C++ 2008
@Дополнительно          :
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef HIMIT_H
#define HIMIT_H

#include "U.h"

namespace imit
{
using namespace COMMON;

// ---------------------------------------------------------------------------
//
// Зона параметров эталона
 // //

struct TEtalon
{
    double          tStart;                 //[c] Время начала имитации объекта  [TH]
    double          tFinish;                //[c]Время окончания имитации объекта [TK]
    double          tExtr;                  //[c] время последней экстраполяции координат[T]
    double          tNextExtr;              //[c] время следующей экстраполяции координат
    double          tMovem;                 //[c]время очередного изменения движения [TKM]
    double          tStartMovem;            //[c] время начала очередного изменения движения[TN]
    float          xReference;             //[м] коорд опорная объекта  [XO]
    float          yReference;             //[м] коорд опорная объекта  [YO]
    float          hReference;             //[м]высота опорная объекта  [VO]
    float          psiReference;           //[град] курс объекта
    float          vReference;             //[м/с]скорость объекта
    float          vxReference;                     //[м] Составляющая вектора скорости
    float          vyReference;                     //[м/с] Составляющая вектора скорости
    float          vh;                     //[м/с2] ускорение
    float          a;                      //[м/с2] ускорение
    float          r;                      //[м] радиус разворота
    unsigned char   countManevr,            //количество маневров     [KM]
                    numberManevr,           //номер маневра           [TNM]
                    sensLoss1,              //номер 1источника,потерявшего трассу [NI1]
                    sensLoss2,              //номер 2источника,потерявшего трассу  [NI2]
                    meterLoss1,             //счетчик количества обзоров, прошедших с момента последней
                                            //локации 1 источником                 [CH1]
                    meterLoss2,             //счетчик количества обзоров, прошедших с момента последней
                                            //локации 2 источником                 [CH2]
                    meterEndTrack;          //счетчик конца трассы, сброс после 7 обзоров
    EUObjClass     ObjClass;                // Класс объекта
                                               //UOC_AIR     = 1,     Воздушный (AIR)
                                               //  UOC_SEA     = 2,     Надводный (SEA)
                                               // UOC_GROUND  = 3,     Наземный (GROUND)
     double           tNextGivSens[SENS_MAX];     // время выдачи донесения о даннном эталоне,
                                            // индекс элемента массива соответствует номеру источника информации
                                            // ИИ назначен на имитацию
    int             IO;                        // Не опознан,=3- воздушный противник
    int             TO;                      // типа воздушного объекта.=8-ГЗЛА, =10-БР, =11-КР, =14-СА

    EUOGP           OGP;                    // ОГП
   bool         trackEnd;               // признак конца трассы
    bool         trackBZ;                // формуляр занят  (YES-занят) [ZF]


    struct TManevr
    {        //зона маневров эталона
      double       tStart;                  //[c] Время начала маневра
      double       tFinish;                 //[c] Время окончания маневра
      float       a;                       //[м/с2] ускорение
      float       vh;                      //[м/с]скорость изменения высоты
      float       r;                       //[м] радиус разворота
    } Manevr[10] ;                             //
};

//// ---------------------------------------------------------------------------
//
//  Связка трассы источника с номером эталона
//

struct TSensTrcLink
{
    unsigned int   Trc;                     // номер  трассы
};

} // namespace imit

#endif /* HIMIT_H */
