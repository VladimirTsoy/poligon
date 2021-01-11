         
              //  TGeneralTrack
#ifndef _TGENERALTRACKAIR_H
#define _TGENERALTRACKAIR_H

#include "TGenTrcSAir.h"

#include "AdjustmentCommon.h"

namespace PTPV
{

namespace air
{
using namespace COMMON;

      // Обобщённая трасса
	
      class TGeneralTrack
        {
        private:
		unsigned int NextRecord [UGEN_TRC_MAX + 1];
		unsigned int firstRecord;
		unsigned int lastRecord;

		TGenTrcS GenTrcS [UGEN_TRC_MAX];
        
        public:
        

 //       static TGenTrcS CGenTrcS0 ;


        // инициализация переменных информационных модулей
        void Init(void);

        // занятие формуляра
        unsigned int CreatRecord(void);

        // освобождение формуляра
        void DestroyRecord(unsigned int namberTrack);

        // определение занятости формуляра
        unsigned int Record(unsigned int namberTrack);

        TGenTrcS &operator[] (unsigned int i);
		const TGenTrcS &operator[] (unsigned int i) const;

        TGeneralTrack() {};

        };
	
} // namespace air

} // namespace PTPV

#endif // _TGENERALTRACKAIR_H

