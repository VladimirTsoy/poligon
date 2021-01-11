/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
@Copyright (c)  		       : 
       Центр МНИИПА ОАО "ГСКБ "Алмаз-Антей"
@Имя файла    		       :
       DefAir.h
@Описание  		       :
       Константы функциональной задачи обработки информации по ВО
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
 
            //  Константы Air
#ifndef _DEFAIR_H        
#define _DEFAIR_H

namespace PTPV
{

namespace air
{
	
	             // константы отбора
	
	const int FIRST_SELECT = 1;         // минимальный номер трассы на отбор
	                                    // по данным оповещения управляющим КП
	const int ALIVE_SELEKT_MAX = 4;     // максимальное количество отобранных
	                                    // "живых" трасс
	const float DIF_DEAD_PSI = 1.57f;   // строб отбора "мёртвых" трасс по курсу 
	const double DIF_DEAD_T = 30.;      // продолжительность хранения
	                                    // "мёртвых" трасс 
	const float DIF_H = 6000.f;         // строб отбора трасс по высоте
	const float DIF_XY = 10000.f;       // строб отбора трасс по координатам
	
	             // константы отождествления
	
	const double DIF_IDENT_XY = 3000.;      // строб отождествления трасс по
	                                        // координатам
	const float DIF_IND_NUM_XY = 15000.f;   // строб отождествления трасс по
	                                        // индивидуальному номеру
	
	             // константы переотождествления
	
	const double DIF_IND_NUM_T = 60.;    // время старения информации об
	                                     // индивидуальном номере
	const double DIF_CHECK_XY = 5000.;   // строб сопровождения трасс
	                                     // по координатам
	const int MISMAT_XY_COUNT = 3;       // максимальное значение счётчика
	                                     // несоответствия трассы источника
	                                     // обобщённой трассе по координатам
	const int MISMAT_SENS_COUNT = 3;     // максимальное значение счётчика
	                                     // несоответствия обобщённой трассы по
	                                     // количеству источников сопровождения
	
	         // константы последовательного анализа
	
	const int SEQ_CANDIDATE_MAX = 4;      // максимальное количество кандидатов
	                                      // последовательного анализа
	const int LIMIT_STEP_MAX = 8;         // максимальное количество шагов
	                                      // принятия решения
	const int LIMIT_STEP_MIN = 5;         // минимальное количество шагов
	                                      // принятия решения
	const double FUZZY_KOEF = 0.000001;   // коэффициент нечёткой функции
	const double CRIT_MIN = 1.;           // нижний порог
	                                      // последовательного анализа при
	                                      // первой проверке (отождествление)
	const double CRIT_MAX = 100.;         // верхний порог последовательного
	                                      // анализа при первой проверке (новая)
	const double CRIT = 20.;              // порог последовательного
	                                      // анализа при последней проверке
	
	             // константы сопровождения
	
	const float EXTENS_TRUST_XY = 50.;
	const float EXTENS_TRUST_H = 50.;
	const double FILTER_M_XY = 0.7f;
	const double FILTER_M_V = 40.;
	const double DIF_M_FILTER_XY = 12000.;
	const double FILTER_XY = 0.3f;
	const double FILTER_V = 60.;
	const double DIF_FILTER_XY = 8000.;
	const double DIF_FILTER_V_T = 3.;
	const double RATIO_FILTER_H=0.3;
	const double RATIO_CHANGE_H=0.7;
		
} // namespace air

} // namespace PTPV

#endif // _DEFAIR_H
