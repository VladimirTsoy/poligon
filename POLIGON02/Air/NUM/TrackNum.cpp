#include "TrackNum.h"

namespace N_U_M
{
TrackNum::TrackNum():TrcNum()
{

}

//getter
int TrackNum::GetIvo()
{
    return ivo;
}


int TrackNum::GetTvo()
{
    return tvo;
}


int TrackNum::GetNe()
{
    return ne;
}

//setter
void TrackNum::SetIvo(int ivo)
{
    this->ivo = ivo;
}


void TrackNum::SetTvo(int tvo)
{
    this->tvo = tvo;
}


void TrackNum::SetNe(int ne)
{
    this->ne = ne;
}


}
