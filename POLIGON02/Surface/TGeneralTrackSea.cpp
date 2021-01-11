/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
@Copyright (c)          : ОАО "РТИ"
@Имя файла              : TGeneralTrackSea.cpp
@Описание               : Определение методов класса зоны обобщённых трасс
                          надводных (морских) и наземных объектов и методов
                          вложенного класса длины кодовых последовательностей.
@Замечания              : Определение класса и встроенных методов
                          содержатся в файле TGeneralTrackSea.h.
@Автор                  : Самсон С. Ю.
@Дата                   : 26.08.2015
@Инструментальная среда : Microsoft Visual C++ 2012
@Дополнительно          : Класс носит имя BIUS_A100::PTPV::sea::GeneralTrack.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <string.h>

#include "TGeneralTrackSea.h"

#include "OSLibFacilitiesAccomodation.h"

namespace PTPV
{

namespace sea
{
	
      // Обобщённая трасса

//      TGenTrcS  TGeneralTrack :: CGenTrcS0;

TGeneralTrack::TGeneralTrack()
{
	int i;
	NextRecord[0] = 0;
	for ( i = 1; i < UGEN_SURFACE_TRC_MAX ;i++ )
		NextRecord[i] = i + 1;
	NextRecord[UGEN_SURFACE_TRC_MAX] = 0;
	firstRecord = 1;
	lastRecord = UGEN_SURFACE_TRC_MAX;
}


	unsigned int TGeneralTrack :: CreatRecord(void)
      {
      int num;
      if ( firstRecord!= 0)
        {
        num = firstRecord;
        firstRecord = NextRecord[num];
        NextRecord[num] = 0;
        if ( firstRecord== 0)
          lastRecord=0;
        return num;
        }
      else
        return 0;
      }

   void TGeneralTrack :: DestroyRecord(unsigned int numTrc)
     {
     if(firstRecord==0)
       {
       firstRecord=numTrc;
       lastRecord=numTrc;
       }
     else
       {
       NextRecord[lastRecord]=numTrc;
       lastRecord=numTrc;
       }
     }

   unsigned int TGeneralTrack ::Record(unsigned int numTrc) const
      {
      if((NextRecord[numTrc]==0)||(lastRecord==numTrc))
        // формуляр занят
        return 1;
      else
        // формуляр свободен
        return 0;
      }

} // namespace sea

} // namespace PTPV
