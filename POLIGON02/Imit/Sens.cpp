
#include <string.h>
#include "Init.h" // временно!
#include "Sens.h"

namespace imit
{
using namespace BIUS_A100; // временно!

Sens::Sens(TDinChar *_dinChar, TMsgTrc *_MsgTrc, TPubEtalon *_pubEtalonImit, TCharSens *_t_char_sens, TSensSite *_t_sens_site) : DinChar(_dinChar), MsgTrc(_MsgTrc), PubEtalonImit(_pubEtalonImit)
{
//    qDebug()<<"Start Sens";

    SensSite = _t_sens_site;
    CharSens = _t_char_sens;

//    qDebug()<<SensSite[1].x;

    /// Формирование зоны связи трасс источников с номером эталона
    for(uint i = 1; i < SENS_MAX; ++i)
    {
        Link[i] = new TSensTrcLink[(CharSens [SensSite[i].sensChar].maxCountTrc+1)];
        for(uint j = 1; j <= CharSens[SensSite[i].sensChar].maxCountTrc; ++j)
        {
            /// Чистка зоны  трасс источников
            Link[i][j].Trc = 0;
        }
    }
}

Sens::~Sens()
{
}
/// Анализ источников сопровождения */
/***********************************************************/
void Sens:: AssaySens(TPubEtalon* pPubEtalon,TEtalon* pEtalon,unsigned int numEt,char racp,double currentT) /*анализ источников сопровождения данной трассы*/

{
    unsigned char  sensNum,sens,rez,copr;
    unsigned int trcNum;
    TSensSite* pSensSite;
    TCharSens* pCharSens;

    for(sensNum = 1;sensNum < SENS_MAX;sensNum++)         //начало цикла по источникам сопровождения
    {   pSensSite = SensSite;
        pCharSens = CharSens;
        pSensSite = pSensSite+sensNum;
        pCharSens = CharSens+pSensSite->sensChar;
       if((pEtalon->ObjClass == 1) && (pSensSite->sensChar > 2))      //  ВО типы 45Л6 или 99Ш6
        continue;
      if((pEtalon->ObjClass == 2) && (pSensSite->sensChar != 3))
        continue;
       if((pEtalon->ObjClass == 3) && (pSensSite->sensChar != 4))    // морской объект не алеврит на конец цикла
   //     if (((pEtalon->ObjClass == 2)||(pEtalon->ObjClass == 3)) && (pSensSite->sensChar != 3))       // морской объект не алеврит на конец цикла
            //        { qDebug() << "ObjClass  " << pEtalon->ObjClass ;
            //            qDebug() << "numEt = " << numEt;
            //             qDebug() << "sensChar " << pSensSite->sensChar;
            continue;
        //}

        copr = 0;
        if(racp == 3)                              //СБРОС
        {   //***************************стирание ИИ из формуляра ВО
            copr = racp;
            sens = sensNum;
            trcNum = pPubEtalon->trcNumSens[sens];
            if (trcNum == 0)
                continue;
            FormTrcMsg(numEt,trcNum,currentT,sens,copr,pCharSens); /*формирование заголовка для PubEtalon(выходное сообщение)*/
            if(sensNum == pEtalon->sensLoss1)    pEtalon->sensLoss1 = pEtalon->meterLoss1 = 0;
            else if(sensNum == pEtalon->sensLoss2)  pEtalon->sensLoss2 = pEtalon->meterLoss2 = 0;
            Link[sensNum][pPubEtalon->trcNumSens[sensNum]].Trc = 0;   //стирание номера трассы
            pPubEtalon->trcNumSens[sensNum] =0;
            continue;
        }
        //*******************************НЕ СБРОС****************************************************
        //*****************************************************************************************
        if( pEtalon->tNextGivSens[sensNum] < currentT)
        {
            pEtalon->tNextGivSens[sensNum] = currentT+10;                    //время следующей выдачи через 10с
            if(DinChar->zoneView )
                rez = 1;                                //зона вимости расширена
            else
                rez =  VisibInvisib1(pPubEtalon,pCharSens,pSensSite);

            if(rez != 0)                                                               //ВИДИТ
                //*************************************************************************************************
            {
                if(pPubEtalon->trcNumSens[sensNum] == 0) 	 //номер трассы ИИ =0  НОВАЯ
                {
                    copr = 1;                                  //новая трасс
                    //*****************************/*вписывание источника сопровождения данной трассы*/
                    for(trcNum = 1;trcNum <= CharSens[SensSite[sensNum].sensChar].maxCountTrc+1;trcNum++)
                    {
                        if(Link[sensNum][trcNum].Trc == 0)
                        {
                            pPubEtalon->trcNumSens[sensNum] = trcNum;
                            Link[sensNum][trcNum].Trc = numEt;
                            break;
                        }
                    }
                }
                else
                {   copr = 2;                                //обновление координат
                    if(sensNum == pEtalon->sensLoss1)    pEtalon->sensLoss1 = pEtalon->meterLoss1 = 0;
                    else if(sensNum == pEtalon->sensLoss2)  pEtalon->sensLoss2=pEtalon->meterLoss2 = 0;
                }
            }
            //*************************************************НЕ ВИДИТ****************************************
            else
            {
                if(pPubEtalon->trcNumSens[sensNum] == 0)                      //номер трассы =0 КД не выдавались
                    continue;
                if(sensNum == pEtalon->sensLoss1)
                {
                    if(++pEtalon->meterLoss1 > END_TRACK_MAX)                //сброс источника после 7 обзоров
                    {
                        copr = 3;				 //СБРОС
                        //***************************стирание ИИ из формуляра ВО
                        sens = sensNum;
                        trcNum = pPubEtalon->trcNumSens[sens];
                        FormTrcMsg(numEt,trcNum,currentT,sens,copr,pCharSens); /*формирование заголовка для PubEtalon(выходное сообщение)*/
                        pEtalon->sensLoss1 = pEtalon->meterLoss1 = 0;
                        Link[sensNum][pPubEtalon->trcNumSens[sensNum]].Trc = 0;   //стирание номера трассы
                        pPubEtalon->trcNumSens[sensNum] = 0;
                    }
                    continue;
                }
                else
                {
                    if(sensNum == pEtalon->sensLoss2)
                    {
                        if(++pEtalon->meterLoss2 > END_TRACK_MAX)                 //сброс источника после 7 обзоров
                        {
                            //***************************стирание ИИ из формуляра ВО
                            sens = sensNum;
                            trcNum = pPubEtalon->trcNumSens[sens];
                            FormTrcMsg(numEt,trcNum,currentT,sens,copr,pCharSens); /*формирование заголовка для PubEtalon(выходное сообщение)*/
                            pEtalon->sensLoss2 = pEtalon->meterLoss2 = 0;
                            Link[sensNum][pPubEtalon->trcNumSens[sensNum]].Trc = 0;   //стирание номера трассы
                            //                           pPubEtalon->noInform[sensNum] =
                            pPubEtalon->trcNumSens[sensNum] = 0;
                            copr = 3;				 //СБРОС
                        }
                        continue;
                    }
                    if(pEtalon->sensLoss1 == 0)
                    {
                        pEtalon->sensLoss1 = sensNum;
                        pEtalon->meterLoss1 = 1;
                    }
                    else
                    {
                        if(pEtalon->sensLoss2 == 0)
                        {
                            pEtalon->sensLoss2 = sensNum;
                            pEtalon->meterLoss2 = 1;
                        }
                        else
                        {
                            if(pEtalon->meterLoss2 < pEtalon->meterLoss1)
                            {
                                sens = pEtalon->sensLoss1;
                                pEtalon->sensLoss1 = sensNum;
                                pEtalon->meterLoss1 = 1;
                            }
                            else
                            {
                                sens = pEtalon->sensLoss2;
                                pEtalon->sensLoss2 = sensNum;
                                pEtalon->meterLoss2 = 1;
                            }
                            //***************************стирание ИИ из формуляра ВО
                            trcNum = pPubEtalon->trcNumSens[sens];
                            FormTrcMsg(numEt,trcNum,currentT,sens,copr,pCharSens); /*формирование заголовка для PubEtalon(выходное сообщение)*/
                            pEtalon->sensLoss2 = pEtalon->meterLoss2 = 0;
                            Link[sens][pPubEtalon->trcNumSens[sens]].Trc = 0;   //стирание номера трассы
                            pPubEtalon->trcNumSens[sens] =0;
                            //                                       pPubEtalon->sensImit[sens] = 0;   //стирание ИИ из формуляра ВО
                            copr = 3;				 //СБРОС
                        }
                    }
                }
            }
            sens=sensNum;
            trcNum = pPubEtalon->trcNumSens[sens];
            FormTrcMsg(numEt,trcNum,currentT,sens,copr,pCharSens); /*формирование заголовка для PubEtalon(выходное сообщение)*/
        }
    }
}

/// Формирование заголовка для PubEtalon(выходное сообщение)
void Sens::FormTrcMsg(unsigned int numEt, unsigned int trcNum, double currentT, short int sens, char copr, TCharSens *pCharSens)
{
    TMsgTrc *pMsgTrc;
    pMsgTrc = MsgTrc;
    ++DinChar->countMessage;    // количество сообщений +
    pMsgTrc = pMsgTrc + DinChar->countMessage;
    pMsgTrc->numEt = numEt;
    pMsgTrc->trcNum = trcNum;
    pMsgTrc->currentT = currentT;
    pMsgTrc->numSens = sens;
    pMsgTrc->sensChar = SensSite[sens].sensChar;
    pMsgTrc->copr = copr;
    pMsgTrc->trustXY =pCharSens-> trustXY;
    pMsgTrc->trustH =pCharSens-> trustH;


}
/// Стирание (сброс) источника из формуляра
void Sens::SensEnd(TPubEtalon* pPubEtalon,short int sens) /*стирание источника из формуляра*/
{
    Link[sens][pPubEtalon->trcNumSens[sens]].Trc = 0;   //стирание номера трассы
    pPubEtalon->trcNumSens[sens] =0;

}

/*анализ местонахождения ВО относительно ИИ*/
int Sens:: VisibInvisib1(TPubEtalon* pPubEtalon,TCharSens* pCharSens,TSensSite* pSensSite)
{
    float r;
    unsigned char  rez=0;
    if((pPubEtalon->h > pCharSens->hMin) && (pPubEtalon->h <= pCharSens->hMax))
    {
        r = sqrt(pow(pSensSite->x - pPubEtalon->x, 2) + pow(pSensSite->y - pPubEtalon->y, 2));     //№[(X-Xo)*(X-Xo)+(Y-Yo)Y-Yo)}
        if((r <= pCharSens->rMax)&&(r >= pCharSens->rMin))
            rez = 1;                                   //ВО находится в зоне обнаружения ИИ
    }
    return rez;
}


} // namespace imit
