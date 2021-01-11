#include "Task.h"

namespace N_U_M
{

Task::Task(){}

void Task::Init(const COMMON::_PTPV_::TUTrcMsg msg,
                PTPV::air::TMsgProc* pMsgProc,
                PTPV::air::PTPV_TGenTrc* genTrc,
                TrcNum* trcNum,
                PTPV::air::TSensorDescription* curSensor,
                PTPV::air::TGeneralTrack* allTrc)
{
    this->allTrc = allTrc;
    this->pMsgProc = pMsgProc;

    for(int i=0;i<2;i++)
    {
        if (pMsgProc->Update[i].trcUpdate == 1)
        {
            inputMsg.Init(pMsgProc->Update[i].trcNum,msg);
            break;
        }
    }

    this->curSensor = curSensor;
    this->genTrack = new GenTrack(genTrc,trcNum);

}

void Task::Free()
{
    delete this->genTrack;
}

//getter

Msg* Task::GetInputMsg()
{
    return &inputMsg;
}

PTPV::air::TMsgProc* Task::GetPMsgProc()
{
    return pMsgProc;
}


GenTrack* Task::GetGenTrack()
{
    return genTrack;
}

PTPV::air::TSensorDescription* Task::GetCurSensor()
{
    return curSensor;
}


TrackNum* Task::GetMiddleNum()
{
    return &middleNum;
}

PTPV::air::EUTrcState Task::GetState()
{
    return this->state;
}


//setter
void Task::SetState(PTPV::air::EUTrcState state)
{
    this->state = state;
}
}
