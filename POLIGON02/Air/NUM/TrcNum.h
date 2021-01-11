#ifndef TRCNUM_H
#define TRCNUM_H

//данные о НУМ по трассе

#include <QList>
#include <QString>

namespace N_U_M
{
class TrcNum
{
public:
    TrcNum();

    //getter
    int GetSensorIvo();
    int GetSensorTvo();

    bool IsOneMaxRankIvo();
    bool IsOneMaxRankTvo();

    QList<int>* GetList(QString str);

    //setter
    void SetSensorIvo(int sensorIvo);
    void SetSensorTvo(int sensorTvo);

/****************/

    void AddSensorIvo(int numberAddSensor);
    void DeleteSensorIvo(int numberDelSensor);

    void AddSensorTvo(int numberAddSensor);
    void DeleteSensorTvo(int numberDelSensor);

    void FreeSensorLstIvo();
    void FreeSensorLstTvo();


private:
    //приватные функции
    void ReCount(bool& bRank,QList<int>* lst);  //пересчет единственности источника

    //переменные
    int sensorIvo;                              //номер источника, присвоивший ИВО
    bool oneMaxRankIvo;                         //один ли источник, по которому задается ранг ИВО
    QList<int> lstIvo;                          //массив источников (присылающих ИВО), ведущих данный ВО

    int sensorTvo;                              //номер источника, присвоивший ТВО
    bool oneMaxRankTvo;                         //один ли источник, по которому задается ранг ТВО
    QList<int> lstTvo;                          //массив источников (присылающих ТВО), ведущих данный ВО

};
}
#endif // TRCNUM_H
