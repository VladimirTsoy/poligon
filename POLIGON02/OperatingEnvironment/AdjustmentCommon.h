			  // Включение общих заголовочных файлов ФПО БИУС с учётом
			  // возможного отличия стандарта библиотеки C++, поддерживаемой
			  // используемым инструментальным средством разработки ТОИ

#ifndef _ADJUSTMENTCOMMON_H
#define _ADJUSTMENTCOMMON_H

#include "OSInstantiation.h"

namespace PTPV {

// Используется стандарт C++, не поддерживающий <stdint.h>:
#if defined __OLDSTD
#if	((defined MVISUAL) || (defined BORLAND))
#define int32_t  __int32
#define uint32_t unsigned __int32
#else
// определения 4-байтового платформонезависимого целого для иных компиляторов
#endif
#endif

} // namespace PTPV

#include "U_PTPV_.h"

namespace PTPV {

#undef int32_t
#undef uint32_t

} // namespace PTPV

#endif /* _ADJUSTMENTCOMMON_H */
