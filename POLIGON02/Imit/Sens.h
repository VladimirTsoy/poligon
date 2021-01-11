#ifndef SENS_H
#define SENS_H

#include "_IMIT_.h"
#include "HImit.h"

namespace imit
{
using namespace COMMON::_IMIT_;

class Sens
{
public:
    Sens(TDinChar *_dinChar, TMsgTrc *_MsgTrc, TPubEtalon *_pubEtalonImit, TCharSens * _t_char_sens, TSensSite * _t_sens_site);
    ~Sens();

    void AssaySens(TPubEtalon* pPubEtalon,TEtalon* pEtalon,unsigned int numEt,char racp,double currentT); /*анализ источников сопровождения данной трассы*/
    void FormTrcMsg(unsigned int numEt, unsigned int trcNum,double currentT,short int sens,char copr,TCharSens* pCharSens);/*формирование заголовка для PubEtalon(выходное сообщение)*/
    void SensEnd(TPubEtalon* pPubEtalon,short int sens);            /*стирание источника из формуляра*/
    int VisibInvisib1(TPubEtalon* pPubEtalon,TCharSens* pCharSens,TSensSite* pSensSite);   /*анализ местонахождения ВО относительно ИИ*/
    // * Связка трассы источника с номером эталона */
    TSensTrcLink *Link[SENS_MAX];
    TDinChar *DinChar;
    TMsgTrc *MsgTrc;
    TPubEtalon *PubEtalonImit;

    TCharSens * CharSens;
    TSensSite * SensSite;
};

} // namespace imit

#endif /* SENS_H */
