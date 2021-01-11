#include "TrcNum.h"

namespace N_U_M
{
TrcNum::TrcNum()
{

}

//getter
int TrcNum::GetSensorIvo()
{
    return this->sensorIvo;
}

int TrcNum::GetSensorTvo()
{
    return this->sensorTvo;
}

bool TrcNum::IsOneMaxRankIvo()
{
    return this->oneMaxRankIvo;
}

bool TrcNum::IsOneMaxRankTvo()
{
    return this->oneMaxRankTvo;
}


QList<int>* TrcNum::GetList(QString str)
{
    if(str == "ivo")
        return &(this->lstIvo);
    else
        return &(this->lstTvo);
}

//setter
void TrcNum::SetSensorIvo(int sensorIvo)
{
    this->sensorIvo = sensorIvo;
}

void TrcNum::SetSensorTvo(int sensorTvo)
{
    this->sensorTvo = sensorTvo;
}

/***********************/

void TrcNum::AddSensorIvo(int numberAddSensor)
{
   if(!lstIvo.contains(numberAddSensor))
   {
       lstIvo.append(numberAddSensor);
   }

    ReCount(oneMaxRankIvo,&lstIvo);
}



void TrcNum::DeleteSensorIvo(int numberDelSensor)
{
    for(int i=0; i<lstIvo.count(); i++)
    {
        if(lstIvo.at(i) == numberDelSensor)
        {
            lstIvo.removeAt(i);
            ReCount(oneMaxRankIvo,&lstIvo);
            break;
        }
    }
}

void TrcNum::AddSensorTvo(int numberAddSensor)
{
   if(!lstTvo.contains(numberAddSensor))
   {
       lstTvo.append(numberAddSensor);
   }

    ReCount(oneMaxRankTvo,&lstTvo);
}



void TrcNum::DeleteSensorTvo(int numberDelSensor)
{
    for(int i=0; i<lstTvo.count(); i++)
    {
        if(lstTvo.at(i) == numberDelSensor)
        {
            lstTvo.removeAt(i);
            ReCount(oneMaxRankTvo,&lstTvo);
            break;
        }
    }
}

void TrcNum::FreeSensorLstIvo()
{
    lstIvo.clear();
}

void TrcNum::FreeSensorLstTvo()
{
    lstTvo.clear();
}

void TrcNum::ReCount(bool& bRank,QList<int>* lst)
{
    if(lst->count()==1)
    {
        bRank = true;
    }
    else
    {
        bRank = false;
    }
}
}
