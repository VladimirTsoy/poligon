#ifndef GENTRACK_H
#define GENTRACK_H

#include "HAir.h"
#include "TrcNum.h"

#include <QString>
//класса объединяющий общую обобщенную трассу и данные о НУМ по трассе

namespace N_U_M
{
class GenTrack
{
public:
    GenTrack(COMMON::_PTPV_::PTPV_TGenTrc* genTrc,TrcNum* trcNum);

    //getter
    int GetIvo();
    int GetTvo();
    int GetNe();

    int GetSensorIvo();
    int GetSensorTvo();

    int GetCountSensor();
    int* GetArraySensor();

    bool IsOneMaxRankSIvo();
    bool IsOneMaxRankSTvo();

    double GetSpeed();
    double GetHeight();

    QList<int>* GetList(QString str);               //установить список источников ИВО/ТВО

    //setter
    void SetIvo(int ivo);
    void SetTvo(int tvo);
    void SetNe(int ne);

    void SetSensorIvo(int sensorIvo);
    void SetSensorTvo(int sensorTvo);


/***********************/
    void AddSensorIvo(int numberAddSensor);
    void DeleteSensorIvo(int numberDelSensor);

    void AddSensorTvo(int numberAddSensor);
    void DeleteSensorTvo(int numberDelSensor);

    void FreeSensorLstIvo();
    void FreeSensorLstTvo();




private:
    PTPV::air::PTPV_TGenTrc* genTrc;
    TrcNum* trcNum;
};
}
#endif // GENTRACK_H
