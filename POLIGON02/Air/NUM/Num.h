#ifndef NUM_H
#define NUM_H

#include "DispatcherTable.h"
#include "S_E_Num.h"
/// #include <QList>
#include "Task.h"
#include "../HAir.h"
#include "DispatcherNe.h"
#include "S_E_Num.h"
/// #include <QDebug>
#include <ctime>
#include "TrcNum.h"


namespace N_U_M
{
class Task;

////диспетчер, отвечающий за нумерацию и индексацию
class Num
{
public:
    Num();

    ///иницализация класса, принимающего решение по НУМ
    void Init(PTPV::air::TSensorDescription* SensorDescription,  //указатель на источники
              PTPV::air::TGeneralTrack* GeneralTrack,            //указатель на обобщенные трассы
              PTPV::air::TSensGenTrcLink **Link,
              const char* fileIvo,                               //файлы, содержащие таблицы принятия решений по НУМ
              const char* fileTvo
              /*,const char* fileIvoTvo*/);

    ///вызов диспетчера  процесса нумерации и индексации по обработке сообщения
    void MsgTaskChain(const COMMON::_PTPV_::TUTrcMsg &msg,              //входное сообщение
                     PTPV::air::TMsgProc* pMsgProc);

    ///вызов диспетчера задач процесса нумерации и индексации по периодическим ситуациям
    void StateTaskChain(PTPV::air::TStateProc *pStateProc);                               /*явный вызов переменных структуры pStateProc (!!!) */

private:
    ///===================================
    ///приватные функции
    //-------------------------

    void MainWork();
    void Work(unsigned char add, unsigned char del);//основная обработка сообщения
    void InitState();                       //определение состояния трассы
    void UpdateGenTrack();                  //обновление обобщенной трасса по НУМ в результате обработки сообщения

    void CopyListsIn();                     //копирование массивов источников ИВО и ТВО из обобщенной трассы в текущую результирующую
    void CopyListsOut();                    //копирование массивов источников ИВО и ТВО из текущей результирующей в обобщенную трассу

    void HandlingIvo();                     //обработка ИВО

    bool HandlingTvo();                     //обработка ТВО
    int GetThreatTvo(int tvo);              //определение уровня угрозы ТВО

    void HandlingNe();                      //обработка единых номеров
    void HandlingLink();

    //временные функции
    void SetRankSensor(PTPV::air::TSensorDescription* SensorDescription);    //установка ранга источникам


    ///===================================
    ///переменные
    //-------------------------

    DispatcherTable dispatcherTable;                  //обработчик файлов, содержащих таблицы принятия решений по НУМ
    TableNum tableNum;                                //таблицы принятия решений по НУМ
    DispatcherNe dispatcherNe;                        //личный диспетчер единых номеров
    PTPV::air::TSensorDescription* SensorDescription; //указатель на массив источников

    PTPV::air::TSensGenTrcLink **Link; //размер SENS_MAX + 1

    Task currentTask;                                 //текущее задание

    PTPV::air::TGeneralTrack* aTrc;                   //указатель на массив обобщенных трасс
    TrcNum aTrcNum[COMMON::UGEN_TRC_MAX];          //массив личной инфомации НУМ по обобщенным трассам (доп. к обобщенной трассе)
};
}
#endif // NUM_H
