#include <math.h>
#include "Poi.h"

using namespace COMMON;

Poi::Poi()
{
}

void Poi::PackMsg(const TPubEtalon &pPubEtalon, const TMsgTrc &tMsgTrc, TUTrcMsg *Msg, double T)
{
    memset(Msg, 0, sizeof(TUTrcMsg));

//    Msg->msgTime        = T;                                    /// Реальное время
//     qDebug() << "T"<<T;
    Msg->x              = pPubEtalon.x;                         /// Координата X
    Msg->y              = pPubEtalon.y;                         /// Координата Y
    Msg->h              = pPubEtalon.h;                         /// Высота
    Msg->v              = pPubEtalon.v;                         /// Скорость объекта
    Msg->psi            = pPubEtalon.psi;                       /// Курс объекта
    Msg->vX = pPubEtalon.v * cos(pPubEtalon.psi);               /// Сoставляющая скoрoсти по X
    Msg->vY = pPubEtalon.v * sin(pPubEtalon.psi);               /// Сoставляющая скoрoсти по Y
    Msg->t= Msg->msgTime = tMsgTrc.currentT;                     /// Текущее время
        //qDebug() << "currentT"<<tMsgTrc.currentT;
    Msg->sensNum        = tMsgTrc.numSens;                      /// Номер источника
    Msg->trcNum         = tMsgTrc.trcNum;                       /// Номер трассы
    Msg->trcState       = (EUTrcState) tMsgTrc.copr;            /// Сопр
    Msg->OGP            = /*T < 150. ? (EUOGP)0 : */(EUOGP) pPubEtalon.OGP;

    if(pPubEtalon.manevr == EU_YES)
        Msg->manevr     = pPubEtalon.manevr ? EU_YES : EU_NO;

    Msg->manevrUpdate   = 1.0;
    Msg->OGPUpdate      = 1.0;
    Msg->quant          = 1.0;
    Msg->quantUpdate    = 1.0;
    Msg->xyUpdate       = 1.0;
    Msg->hUpdate        = 1.0;
    Msg->trustXY        = tMsgTrc.trustXY;
    Msg->trustH         = tMsgTrc.trustH;
    Msg->imitObj        = EU_NO; //// (_PTPV_::EUYesNo) pPubEtalon.imitObj; /// Признак имитационного объекта      [TRT]
    Msg->IO       = pPubEtalon.IO;
    Msg->TO       = pPubEtalon.TO;
    Msg->objClass       = pPubEtalon.ObjClass;
//if((Msg->sensNum == 2) && (pPubEtalon.TO != 51 ))
//    if((Msg->sensNum == 2) && (Msg->trcNum == 5 ))
//         {
//          Msg->IO = Msg->TO = 0;
//          Msg->OGP = EU_OGP_UNKNOWN;
//         }




/*
    if(tMsgTrc.sensChar == 2)                      /// Тип источника
    {
        if ((Msg->TVO != EU_TVO_ROCKET_BALL) && ( Msg->TVO != EU_TVO_HS_AIRCRAFT))
            Msg->TVO =  EU_TVO_UNKNOWN;
        Msg->IVO = EU_IVO_UNKNOWN;
    }

    if(tMsgTrc.sensChar == 1)                      /// Тип источника
    {
        if((Msg->TVO != EU_TVO_ROCKET_CR) && ( Msg->TVO != EU_TVO_AVIATION_STRATEG))
            Msg->TVO =  EU_TVO_UNKNOWN;
        Msg->uniNum  = 10000 - tMsgTrc.numEt; // Номер единый
    }
*/
      //   EU_TVO_UNKNOWN   = 0,    // Не опознан,=8-ГЗЛА, =10-БР, =11-КР, =14-СА
      //   EU_TVO_HS_AIRCRAFT   = 8,    // HYPERSONIC_AIRCRAFT =8-ГЗЛА,
      //   EU_TVO_ROCKET_BALL   = 10,    //  =10-БР
      //   EU_TVO_ROCKET_CR = 11,    //  =11-КР
      //   EU_TVO_AVIATION_STRATEG   = 14,    // =14-СА
//    qDebug() << "!POI! TLA = " << (int) Msg->objType;
//    qDebug() << "!POI! trcNum = " << (int) tMsgTrc.trcNum;
//    qDebug() << "!POI! sensNum = " << (int) Msg->sensNum;
//     qDebug() << "!POI! XY = " << (int) Msg->xyUpdate;
//    qDebug() << "!POI! numEt = " << tMsgTrc.numEt;
}
