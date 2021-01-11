			  // Приспособление использования библиотечных средств  
			  // в операционной среде исполнения программы ТОИ 		

#ifndef _OSLIBFACILITIESACCOMODATION_H
#define _OSLIBFACILITIESACCOMODATION_H

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "OSInstantiation.h"

#if defined WINDOWS
#define _WINSOCKAPI_
#include <Windows.h>
#undef _WINSOCKAPI_
#elif defined QNX
#if defined ASTRA
#include <stdlib.h>
#include <time.h>
#endif
#include <pthread.h>
#endif

/* Внимание! Пока может некорретно работать в случае, если в аргументы макроса
   подставляются выражения с побочными эффектами! */
/* Решить проблему можно заменой макросов на функции или
   вызовом функции в макроподстановке. */
#if (defined __OLDSTD) && ((defined MVISUAL) || (defined BORLAND))

#ifndef int32_t
typedef __int32 int32_t;
#endif

#ifndef uint32_t
typedef unsigned __int32 uint32_t;
#endif

#endif

#if !(defined WINDOWS) || (defined BORLAND) 

#ifndef _hypot
#define _hypot hypot
#endif

#ifndef _getch
#define _getch getch
#endif

#else

#define hypot _hypot
#define getch _getch

#endif

#ifndef MVISUAL

#ifndef strcat_s
#define strcat_s(STRDEST, NUMBEROFELEMENTS, STRSOURCE)\
	((STRDEST) == NULL ? \
	EINVAL : \
	(STRSOURCE) == NULL || !(NUMBEROFELEMENTS) ? \
	((STRDEST)[0] = 0, (STRSOURCE) == NULL ? EINVAL : ERANGE) : \
	(strcat((STRDEST), (STRSOURCE)), 0))
#endif

#ifndef strcpy_s
#define strcpy_s(STRDEST, NUMBEROFELEMENTS, STRSOURCE)\
	((STRDEST) == NULL ? \
	EINVAL : \
	(STRSOURCE) == NULL || !(NUMBEROFELEMENTS) ? \
	((STRDEST)[0] = 0, (STRSOURCE) == NULL ? EINVAL : ERANGE) : \
	(strcpy((STRDEST), (STRSOURCE)), 0))
#endif

#ifndef strncpy_s
#define strncpy_s(STRDEST, NUMBEROFELEMENTS, STRSOURCE, COUNT)\
	(!(NUMBEROFELEMENTS) || (STRDEST) == NULL ? \
	EINVAL : \
	(STRSOURCE) == NULL ? \
	((STRDEST)[0] = 0, EINVAL) : \
	((NUMBEROFELEMENTS) > (COUNT) ? \
	(strncpy((STRDEST), (STRSOURCE), (COUNT)), (STRDEST)[(COUNT)] = 0) : \
	strncpy((STRDEST), (STRSOURCE), (NUMBEROFELEMENTS))[0]), \
	0)
#endif

#ifndef  memcpy_s
#define memcpy_s(STRDEST, NUMBEROFELEMENTS, SRC, COUNT)\
	((STRDEST) == NULL ? \
	EINVAL : \
	(SRC) == NULL ? \
	(memset((STRDEST), '\0', (NUMBEROFELEMENTS)), EINVAL) :\
	(memcpy((STRDEST), (SRC), (COUNT)), 0))
#endif

#ifndef fopen_s
#define fopen_s(PFILE, FILENAME, MODE)\
	(errno = 0, \
	(PFILE) != NULL && (FILENAME) != NULL && (MODE) != NULL ? \
	(*(PFILE) = fopen((FILENAME), (MODE)), errno) : \
	EINVAL)
#endif

#ifndef printf_s /* работает только без аргументов в списке) */
#define printf_s(FORMAT)\
	(printf(FORMAT))
#endif
// #ifndef printf_s /* работает только для одного аргумента в списке) */
/*// #define printf_s(FORMAT, ARGUMENT1)\
//	  (printf((FORMAT), (ARGUMENT1))) */
// #endif

#ifndef sprintf_s /* работает только для одного аргумента в списке) */
#define sprintf_s(BUFFER, SIZEOFBUFFER, FORMAT, ARGUMENT1)\
	(sprintf((BUFFER), (FORMAT), (ARGUMENT1)))
#endif

#ifndef _chdir
#define _chdir chdir
#endif

#ifndef _mkdir
#define _mkdir mkdir
#endif

#ifndef _getcwd
#define _getcwd getcwd
#endif

#endif

#ifdef QNX

#ifndef mkdir
#define mkdir(DIRNAME) mkdir(DIRNAME, NULL)
#endif

#ifdef ASTRA
#ifndef getch
#define getch() system("read -s -n 1")
#endif
#endif

#endif

#ifdef MVISUAL
#define strncpy_u(STRDEST, NUMBEROFELEMENTS, STRSOURCE, COUNT, ERRCO)\
	((ERRCO) = strncpy_s((STRDEST), (NUMBEROFELEMENTS), (STRSOURCE), (COUNT)),\
	(STRDEST))

#define memcpy_u(DEST, NUMBEROFELEMENTS, SRC, COUNT, ERRCO)\
	((ERRCO) = memcpy_s((DEST), (NUMBEROFELEMENTS), (SRC), (COUNT)),\
	(DEST))
#else
#define strncpy_u(STRDEST, NUMBEROFELEMENTS, STRSOURCE, COUNT, ERRCO)\
	((ERRCO) = 0, strncpy((STRDEST), (STRSOURCE), (COUNT)))
#define memcpy_u(DEST, NUMBEROFELEMENTS, SRC, COUNT, ERRCO)\
	((ERRCO) = 0, memcpy((DEST), (SRC), (COUNT)))
#endif

#if defined WINDOWS
#define DELAY(MILLISECONDS)\
	Sleep(MILLISECONDS)
#elif defined QNX
#if defined ASTRA
#define DELAY(MILLISECONDS)\
    DelayAccomodation(MILLISECONDS)
#else
#define DELAY(MILLISECONDS)\
	delay(MILLISECONDS)
#endif
#endif

#if defined WINDOWS

typedef CRITICAL_SECTION TCRITICAL_SECTION_DESCR;

#define INIT_CRITICAL_SECTION(PCRITICAL_SECTION_DESCR)\
	InitializeCriticalSection( PCRITICAL_SECTION_DESCR )

#define DELETE_CRITICAL_SECTION(PCRITICAL_SECTION_DESCR)\
	DeleteCriticalSection( PCRITICAL_SECTION_DESCR )

#define ENTER_CRITICAL_SECTION(PCRITICAL_SECTION_DESCR)\
	EnterCriticalSection( PCRITICAL_SECTION_DESCR )

#define LEAVE_CRITICAL_SECTION(PCRITICAL_SECTION_DESCR)\
	LeaveCriticalSection( PCRITICAL_SECTION_DESCR )

#elif defined QNX

typedef pthread_mutex_t TCRITICAL_SECTION_DESCR;

#define INIT_CRITICAL_SECTION(PCRITICAL_SECTION_DESCR)\
	(*(PCRITICAL_SECTION_DESCR) = PTHREAD_MUTEX_INITIALIZER)

#define DELETE_CRITICAL_SECTION(PCRITICAL_SECTION_DESCR)\
	;

#define ENTER_CRITICAL_SECTION(PCRITICAL_SECTION_DESCR)\
	pthread_mutex_lock( PCRITICAL_SECTION_DESCR )

#define LEAVE_CRITICAL_SECTION(PCRITICAL_SECTION_DESCR)\
	pthread_mutex_unlock( PCRITICAL_SECTION_DESCR )

#endif

#if defined WINDOWS

typedef HANDLE TTHREAD_DESTR;
typedef DWORD TRETURN_THREAD_START_ROUTINE;
typedef LPTHREAD_START_ROUTINE TPTHREAD_START_ROUTINE;
  
#define CANCEL_THREAD(THREAD_DESTR)\
	 CloseHandle( THREAD_DESTR )

#elif defined QNX

typedef pthread_t TTHREAD_DESTR;
typedef void *TRETURN_THREAD_START_ROUTINE;
typedef void *(*TPTHREAD_START_ROUTINE)(void *);

#define CANCEL_THREAD(THREAD_DESTR)\
	 pthread_cancel( THREAD_DESTR )

#endif


#if defined ASTRA
	inline void DelayAccomodation(long milliseconds)
	{
		struct timespec req, rem;
		req.tv_sec = milliseconds / 1000;
		req.tv_nsec = milliseconds % 1000 * 1000000;
		while (nanosleep( &req, &rem))
			req = rem;
	}
#endif

#endif /* _OSLIBFACILITIESACCOMODATION_H */
