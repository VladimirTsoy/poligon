
              //  GeneralTrack
#include "TGeneralTrackAir.h"

namespace PTPV
{

namespace air
{


      // Обобщённая трасса

//      TGenTrcS  TGeneralTrack :: CGenTrcS0;
   
          TGenTrcS &TGeneralTrack::operator[] (unsigned int i)
          {
          return GenTrcS[i-1];
          }

    // инициализация переменных информационных модулей
    void TGeneralTrack :: Init(void)
      {
      int i;
      NextRecord[0] = 0;
      for ( i=1 ; i< UGEN_TRC_MAX ; i++ )
        NextRecord[i] = i+1;
      NextRecord[UGEN_TRC_MAX] = 0;
      firstRecord = 1;
      lastRecord = UGEN_TRC_MAX;
      }

    // занятие формуляра
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

   // освобождение формуляра
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

    // определение занятости формуляра
    unsigned int TGeneralTrack ::Record(unsigned int numTrc)
      {
      if((NextRecord[numTrc]==0)||(lastRecord==numTrc))
        // формуляр занят
        return 1;
      else
        // формуляр свободен
        return 0;
      }
 
} // namespace air

} // namespace PTPV
