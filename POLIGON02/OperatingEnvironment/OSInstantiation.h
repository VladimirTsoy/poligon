			  // Указание операционной среды исполнения программы ТОИ

#ifndef _OSINSTANTATION_H
#define _OSINSTANTATION_H

//#define WINDOWS	// программа третичной обработки исполняется в среде ОС Windows
#define QNX     // программа третичной обработки исполняется в среде ОС QNX
                   //                                              либо ОС Linux
#if defined QNX
	#define ASTRA  // программа третичной обработки исполняется в среде Linux
#endif

// #define MVISUAL // программа третичной обработки собирается при помощи
                   // инструментальных средств Microsoft Visual C++ 2008,
                   // предназначенных для изготовления ПО для работы в Windows
// #define BORLAND // программа третичной обработки собирается при помощи 
                   // инструментальных средств Borland 5.02

#endif /* _OSINSTANTATION_H */
