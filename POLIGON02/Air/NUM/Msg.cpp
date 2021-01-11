#include "Msg.h"

//"укороченное" входное сообщение для НУМ

namespace N_U_M
{
Msg::Msg()
{

}

void Msg::Init(int numberTrack, const PTPV::air::TUTrcMsg &msg)
{
    this->trcState = msg.trcState;
    this->ivo = msg.IO;
    this->tvo = msg.TO;
    this->ne = msg.uniNum;
    this->numberTrack = numberTrack;
    this->numberSensor = msg.sensNum;
    this->numberTrackSensor = msg.trcNum;
}

//getter

PTPV::air::EUTrcState Msg::GetTrcState()
{
    return this->trcState;
}


int Msg::GetIvo()
{
    return this->ivo;
}

int Msg::GetTvo()
{
    return this->tvo;
}

int Msg::GetNe()
{
    return this->ne;
}

int Msg::GetNumberSensor()
{
    return numberSensor;
}


int Msg::GetNumberTrack()
{
    return numberTrack;
}


//setter
void Msg::SetIvo(int ivo)
{
    this->ivo = ivo;
}

void Msg::SetTvo(int tvo)
{
    this->tvo = tvo;
}
}
