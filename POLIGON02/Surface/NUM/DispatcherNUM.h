#ifndef DISPATCHERNUM_H
#define DISPATCHERNUM_H


#include "../TGeneralTrackSea.h"
#include "../HSea.h"

namespace N_U_M
{
class DispatcherNUM
{
private:
    PTPV::sea::TSensorDescription* SensorDescription;//указатель на массив источников
    PTPV::sea::TGeneralTrack* aTrc;

public:
    DispatcherNUM();
    void Init(PTPV::sea::TSensorDescription* SensorDescription,
              PTPV::sea::TGeneralTrack* GeneralTrack);
    void MsgTaskChain(const COMMON::_PTPV_::TUTrcMsg &msg,                   //входное сообщение
                      PTPV::sea::TMsgProc* pMsgProc);
    void Work();
};
}

#endif // DISPATCHERNUM_H

