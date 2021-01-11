#include "DispatcherNUM.h"


using namespace COMMON::_PTPV_;

namespace N_U_M
{
DispatcherNUM::DispatcherNUM()
{

}


///вызов диспетчера  процесса нумерации и индексации по обработке сообщения
void DispatcherNUM::MsgTaskChain(const TUTrcMsg &msg,        //входное сообщение
                                 PTPV::sea::TMsgProc* pMsgProc)
{
    for(int i=0;i<2;i++)
    {
        //в случае ести входное сообщение будет обрабатываться
        if ((pMsgProc->Update[i].trcUpdate == 1) && (msg.trcState != 0)/*ПОДПОРКИ*/)
        {
            //основная обработка сообщения

            ((*(this->aTrc))[pMsgProc->Update[i].trcNum].genTrc).TO = msg.TO;

            break;
        }
    }


//    pMsgProc->
}

void DispatcherNUM::Work()
{

}


///иницализация класса, принимающего решение по НУМ
void DispatcherNUM::Init(PTPV::sea::TSensorDescription* SensorDescription,
                         PTPV::sea::TGeneralTrack* GeneralTrack)
{
    aTrc = GeneralTrack;                                         //сохраняем ссылку на массив обобщенных трасс
    this->SensorDescription = SensorDescription;                 //сохраняем ссылку на массив информаций об источниках
}
}
