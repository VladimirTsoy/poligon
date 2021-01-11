#include "GenTrack.h"

#include "U.h"

namespace N_U_M
{

GenTrack::GenTrack(COMMON::_PTPV_::PTPV_TGenTrc* genTrc,TrcNum* trcNum)
{
    this->genTrc = genTrc;
    this->trcNum = trcNum;

}

//getter
int GenTrack::GetIvo()
{
    return genTrc->IO;
}

int GenTrack::GetTvo()
{
    return genTrc->TO;
}

int GenTrack::GetNe()
{
    return genTrc->uniNum;
}

int GenTrack::GetSensorIvo()
{
    return trcNum->GetSensorIvo();
}

int GenTrack::GetSensorTvo()
{
    return trcNum->GetSensorTvo();
}

int GenTrack::GetCountSensor()
{
    return genTrc->sensCount;
}

int* GenTrack::GetArraySensor()
{
    return genTrc->sensTrcNum;
}

bool GenTrack::IsOneMaxRankSIvo()
{
    return trcNum->IsOneMaxRankIvo();
}
bool GenTrack::IsOneMaxRankSTvo()
{
    return trcNum->IsOneMaxRankTvo();
}

double GenTrack::GetSpeed()
{
    return genTrc->v;
}


double GenTrack::GetHeight()
{
    return genTrc->h;
}

QList<int>* GenTrack::GetList(QString str)              //установить список источников ИВО/ТВО
{
    return this->trcNum->GetList(str);
}

//setter
void GenTrack::SetIvo(int ivo)
{
    genTrc->IO = ivo;
}

void GenTrack::SetTvo(int tvo)
{
    genTrc->TO = tvo;
}

void GenTrack::SetNe(int ne)
{
    genTrc->uniNum = ne;
}

void GenTrack::SetSensorIvo(int sensorIvo)
{
    trcNum->SetSensorIvo(sensorIvo);
}

void GenTrack::SetSensorTvo(int sensorTvo)
{
    trcNum->SetSensorTvo(sensorTvo);
}

/*************************/



void GenTrack::AddSensorIvo(int numberAddSensor)
{
    trcNum->AddSensorIvo(numberAddSensor);
}
void GenTrack::DeleteSensorIvo(int numberDelSensor)
{
    trcNum->DeleteSensorIvo(numberDelSensor);
}

void GenTrack::AddSensorTvo(int numberAddSensor)
{
    trcNum->AddSensorTvo(numberAddSensor);
}

void GenTrack::DeleteSensorTvo(int numberDelSensor)
{
    trcNum->DeleteSensorTvo(numberDelSensor);
}

void GenTrack::FreeSensorLstIvo()
{
    this->trcNum->FreeSensorLstIvo();
}

void GenTrack::FreeSensorLstTvo()
{
    this->trcNum->FreeSensorLstTvo();;
}
}
