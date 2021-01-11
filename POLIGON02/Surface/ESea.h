         
              // ESea
#ifndef _ESEA_H
#define _ESEA_H

namespace PTPV
{

namespace sea
{

// Тип сообщения
enum EMismatIdent
{
MI_NONE     = 0,  // Нет несоответствия
MI_IND_NUM  = 1,  // несоответствие по индивидуальному номеру
MI_CRD       = 2,  // несоответствие по координатам
MI_SENS     = 3   // несоответствие по количеству источников
};

enum EIdentState
{
IS_NONE  = 0,          //  0 - нет трассы
IS_FIRST = 1,          //  1 - приход первого донесения о трассе 
IS_SEQUENT_IDENT =2,   //  2 - трасса на последовательном анализе
IS_IDENT =3,           //  3 - трасса отождествлена безусловно
IS_CONDITION_OGP =4,   //  4 - условное отождествление по ОГП
IS_CONDITION_H =5,     //  5 - условное отождествление по H
IS_CONDITION_OGP_H =6  //  6 - условное отождествление по ОГП и H
};

enum ESeqIdent
{
SI_NEW    = 0,  // новая трасса (нет отождествления)
SI_IDENT  = 1,  // отождествление
SI_WAIT   = 2   // ожидание 
};

} // namespace sea

} // namespace PTPV

#endif // _ESEA_H
