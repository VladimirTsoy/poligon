/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
@Copyright (c)          : ОАО "РТИ"
@Имя файла              : TGeneralTrackSea.h
@Описание               : Определение класса зоны обобщённых трасс
                          надводных (морских) и наземных объектов.
@Замечания              : Определения методов содержатся в
                          файле TGeneralTrackSea.cpp.
@Автор                  : Самсон С. Ю.
@Дата                   : 26.08.2015
@Инструментальная среда : Microsoft Visual C++ 2012
@Дополнительно          : Класс носит имя BIUS_A100::PTPV::sea::GeneralTrack.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifndef _TGENERALTRACKSEA_H
#define _TGENERALTRACKSEA_H 

#include "TGenTrcSSea.h"

#include "AdjustmentCommon.h"

namespace PTPV
{

namespace sea
{
using namespace COMMON;

/* Зона обобщённых трасс надводных (морских) и наземных объектов. */

class TGeneralTrack
{
private:
	unsigned int NextRecord [UGEN_SURFACE_TRC_MAX + 1];
	unsigned int firstRecord;
	unsigned int lastRecord;
	TGenTrcS GenTrcS [UGEN_SURFACE_TRC_MAX];
	
public:
// static TGenTrcS CGenTrcS0 ;
	TGeneralTrack();
	
	unsigned int CreatRecord(void);
	void DestroyRecord(unsigned int numberTrack);
	unsigned int Record(unsigned int numberTrack) const;
	unsigned int operator() (unsigned int numberTrack) const;
	TGenTrcS &operator[] (int i);
}; // class TGeneralTrack


// Проверка занятости номера у формуляра.
inline unsigned int TGeneralTrack::operator()
                    ( const unsigned int numberTrack ) const
{
	return !(NextRecord[numberTrack] || numberTrack == lastRecord);
}

inline TGenTrcS &TGeneralTrack::operator[] (int i)
{
	return GenTrcS[i-1];
}

} // namespace sea

} // namespace PTPV

#endif // _TGENERALTRACKSEA_H
