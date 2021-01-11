/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
@Имя файла    		       :
       DefImit.h
@Описание  		       :
       Константы функциональной задачи имитации ВО
@Замечания    		       :
@Автор 			:
      Рыбакова В.Х.
@Дата   			:
      30.07.2014
@Инструментальная среда	       :
      Microsoft Visual C++9.0.
@Дополнительно   		:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef DEFIMIT_H
#define DEFIMIT_H

namespace imit
{

///  Константы Imit

const int       END_TRACK_MAX = 7;      /// Максимальное количество счетчика конца трассы, сброс после 7 обзоров
const int       CountMessage_MAX = 220;  /// Максимальное количество сообщений на выдачу
const float    Q11 = 0.2;              /// Около 11,5 градуса
const float    Yk1 = 0.0085;           /// 0.5 градус
const float	   Yk15=0.2618;            ///M_PI/12;          //  15 град
const float    Yk70 = 1.2217;          /// 70 градус
const float    Tg1 = 0.0175;           /// tg1 градус=0,0175
const float    Tg70 = 1.2217;          /// tg70 градус=2,747
const float    X100 = 100;             /// 100m
const float    Amax = 10000;           /// 10000m
const float    Gh = 9.8156;            /// 9.8m/c*c
const float    Hrepr = 90000;          /// 90000m
const float    Hdrop = 120000;         /// 30000m
const float    Hrepr2 = 60000;         /// 25000m
const float    D1 = 700000;            /// 700000m =700km
const float    D2 = 300000;            /// 300000m=300km
const float    H4000 = 4000;            /// 4000m =4km
const float    H800 = 800;            /// 800m
const float    H200 = 200;            /// 200m
} // namespace imit

#endif /* DEFIMIT_H */
