#ifndef MSG_H
#define MSG_H

#include "U_PTPV_.h"


#include "../TGeneralTrackAir.h"
#include "S_E_Num.h"

namespace N_U_M
{
class Msg
{
public:
    Msg();
    void Init(int numberTrack, const PTPV::air::TUTrcMsg &msg);

    //getter
    PTPV::air::EUTrcState GetTrcState();

    int GetIvo();
    int GetTvo();
    int GetNe();

    int GetNumberSensor();
    int GetNumberTrack();


    //setter
    void SetIvo(int ivo);
    void SetTvo(int tvo);
private:

    PTPV::air::EUTrcState trcState;      //состояние трассы
    int numberSensor;                               //номер источника
    int ivo;                                        //ИВО
    int tvo;                                        //ТВО
    int ne;                                         //Ne
    int numberTrackSensor;                          //номер трассы в нумерации источника
    int numberTrack;                                //номер трассы в нумерации ТОИ


};
}
#endif // MSG_H
