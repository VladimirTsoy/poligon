#ifndef TASK_H
#define TASK_H

///при обработки каждого сообщения создается задание

#include "Msg.h"
#include "../TGeneralTrackAir.h"
#include "AdjustmentCommon.h"
#include "../OperatingEnvironment/OSInstantiation.h"
#include "HAir.h"
#include <QList>
#include "DispatcherNe.h"
#include "GenTrack.h"
#include "TrackNum.h"
#include <QDebug>
#include "TrcNum.h"


namespace N_U_M
{
class Task
{
public:
    Task();
    void Init(const COMMON::_PTPV_::TUTrcMsg msg,
              PTPV::air::TMsgProc* pMsgProc,
              PTPV::air::PTPV_TGenTrc* genTrc,
              TrcNum* trcNum,
              PTPV::air::TSensorDescription* curSensor,
              PTPV::air::TGeneralTrack* allTrc);
    void Free();            //освободить память


    //getter
    Msg* GetInputMsg();
    PTPV::air::TMsgProc* GetPMsgProc();
    GenTrack* GetGenTrack();                             //получить указатель на текущую обобщенную трассу
    PTPV::air::TSensorDescription* GetCurSensor();       //получить указатель на источник, от которого пришло сообщение
    TrackNum* GetMiddleNum();                            //получить указатель на текущий результат обработки сообщения
    PTPV::air::EUTrcState GetState();                    //получить состояние трассы

    //setter
    void SetState(PTPV::air::EUTrcState state); //установить состояние трассы

private:
    PTPV::air::TGeneralTrack* allTrc;

    PTPV::air::EUTrcState state;                         //состояние трассы (определяем сами)
    TrackNum middleNum;                                  //текущий результат обработки сообщения
    PTPV::air::TMsgProc* pMsgProc;

    Msg inputMsg;                                        //входное сообщение
    GenTrack* genTrack;                                  //указатель на текущую обобщенную трассу
    PTPV::air::TSensorDescription* curSensor;            //указатель на информацию об источнике, от которого получено сообщение

};
}
#endif // TASK_H
