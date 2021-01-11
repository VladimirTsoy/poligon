#include "Num.h"
#include <QDebug>

using namespace COMMON::_PTPV_;
using COMMON::_PTPV_::EUTrcState;

namespace N_U_M
{

Num::Num()
{

}

///иницализация класса, принимающего решение по НУМ
void Num::Init(PTPV::air::TSensorDescription* SensorDescription,  //указатель на источники
               PTPV::air::TGeneralTrack *GeneralTrack,            //указатель на обобщенные трассы
               PTPV::air::TSensGenTrcLink **Link,
               const char* fileIvo,                               //файлы, содержащие таблицы принятия решений по НУМ
               const char* fileTvo
               /*,const char* fileIvoTvo*/)
{
    //читаем таблицы по ИВО и ТВО из файлов
    tableNum.tableIvo = dispatcherTable.ReadIvo(fileIvo);            //читаем таблицу ИВО
    tableNum.tableTvo = dispatcherTable.ReadTvo(fileTvo);            //читаем таблицу ТВО
    //tableNum.tableIvoTvo = dispatcherTable.ReadIvoTvo(fileIvoTvo); //читаем таблицу противоречий ИВО-ТВО

    aTrc = GeneralTrack;                                         //сохраняем ссылку на массив обобщенных трасс
    this->SensorDescription = SensorDescription;                 //сохраняем ссылку на массив информаций об источниках
    this->Link = Link;
    //установка ранга источникам [временно]
    SetRankSensor(SensorDescription);
}

void Num::InitState()                   //определение состояния трассы
{
    PTPV::air::EUTrcState st_msg = currentTask.GetInputMsg()->GetTrcState();
    int countSensor = currentTask.GetGenTrack()->GetCountSensor();

    //(количество источников, ведущих трассу == 1) && (состояние сообщения == НОВОЕ)
    if((countSensor == 1) && (st_msg == EU_TS_NEW))
    {
        //состояние задания = НОВОЕ
        currentTask.SetState(EU_TS_NEW);
    }
    //(количество источников, ведущих трассу > 1)
    else if((countSensor > 1) && (st_msg == EU_TS_NEW))
    {
        //состояние задания = ВЕДУЩЕЕ
        currentTask.SetState(EU_TS_TRK);
    }//(количество источников, ведущих трассу == 1) && (состояние сообщения == ВЕДУЩЕЕ)
    else if(st_msg == EU_TS_TRK)
    {
        //состояние задания = ВЕДУЩЕЕ
        currentTask.SetState(EU_TS_TRK);
    }
    else
    {
        //состояние задания = ЗАВЕРШЕННОЕ
        currentTask.SetState(EU_TS_END);
    }
}

//установка ранга источникам [временно]
void Num::SetRankSensor(PTPV::air::TSensorDescription* SensorDescription)
{
    for(int i=1;i<COMMON::SENS_MAX;i++)
    {
        if(i==5)
            continue;
        SensorDescription[i].rank = 1;
    }
    /** SensorDescription[5].rank = 2; **/
}

///вызов диспетчера  процесса нумерации и индексации по обработке сообщения
void Num::MsgTaskChain(const COMMON::_PTPV_::TUTrcMsg &msg,                   //входное сообщение
                      PTPV::air::TMsgProc* pMsgProc)

{
    for(int i=0;i<2;i++)
    {
        //в случае ести входное сообщение будет обрабатываться
        if ((pMsgProc->Update[i].trcUpdate == 1) && (msg.trcState != 0)/*ПОДПОРКИ*/)
        {
            //инициализируем задание начальными данными
            currentTask.Init(msg,
                             pMsgProc,
                             &((*(this->aTrc))[pMsgProc->Update[i].trcNum].genTrc),
                             &aTrcNum[pMsgProc->Update[i].trcNum],
                             &(this->SensorDescription[msg.sensNum]),
                             aTrc);

            //определяем состояние задания
            InitState();

            int numberTrcOnNumerationSensor = (*(this->aTrc))[pMsgProc->Update[i].trcNum].genTrc.sensTrcNum[msg.sensNum];
            PTPV::air::TSensGenTrcLink * curLink = &Link[msg.sensNum][numberTrcOnNumerationSensor];

            if(curLink->identState!=0)
            {
                curLink->Data->IO = msg.IO;
                curLink->Data->TO = msg.TO;
                curLink->Data->uniNum = msg.uniNum;
            }



            //основная обработка сообщения
            Work(pMsgProc->Update[i].sensAdd,pMsgProc->Update[i].sensDelete);

            //освобождаем память, выделенное под задание
            currentTask.Free();

            break;
        }
    }



}

//основная обработка сообщения
void Num::Work(unsigned char add, unsigned char del)
{
    if ((del == 1) && (add == 1))
    {
        MainWork();
        return;
    }


    if (del == 1)
    {
        //удаляем источник
        //если источник не единственен в массиве источнков, определяющих ИВО
        if(!(this->currentTask.GetGenTrack()->IsOneMaxRankSIvo()))
        {
            //удаляем источник
            this->currentTask.GetGenTrack()->DeleteSensorIvo(this->currentTask.GetInputMsg()->GetNumberSensor());

            //если источник был источником являющимся ИсточникомИВО, то назначаем другой источник из оставшихся в массиве за ИсточникИВО соответственно
            if(this->currentTask.GetInputMsg()->GetNumberSensor() == this->currentTask.GetGenTrack()->GetSensorIvo())
            {
                this->currentTask.GetGenTrack()->SetSensorIvo(this->currentTask.GetGenTrack()->GetList("ivo")->first());
            }
        }


        //если источник не единственен в массиве источнков, определяющих ТВО
        if(!(this->currentTask.GetGenTrack()->IsOneMaxRankSTvo()))
        {
            //htmlFile->Write(this->currentTask.GetInputMsg()->GetNumberTrack(),"tvo",this->currentTask.GetInputMsg()->GetNumberSensor());

            //удаляем источник
            this->currentTask.GetGenTrack()->DeleteSensorTvo(this->currentTask.GetInputMsg()->GetNumberSensor());

            //если источник был источником являющимся ИсточникомТВО, то назначаем другой источник из оставшихся в массиве за ИсточникТВО соответственно
            if(this->currentTask.GetInputMsg()->GetNumberSensor() == this->currentTask.GetGenTrack()->GetSensorTvo())
            {
                this->currentTask.GetGenTrack()->SetSensorTvo(this->currentTask.GetGenTrack()->GetList("tvo")->first());
            }
        }

        return;
    }
    else
    {
        MainWork();
        return;
    }
}

/*
     *
     *
     *
     */
void Num::MainWork()
{

    //копираем массивы ИсточниковИВО, ИсточниковТВО из обобщенной трассы в будущую обобщенную трассу
    CopyListsIn();

    //определяем ИВО будущей обобщенной трассы
    HandlingIvo();                              //обработка ИВО

    //определяем ТВО будущей обобщенной трассы
    if(HandlingTvo())                           //при удачной обработки ТВО (без УТВО)
    {
        //определяем Ne будущей обобщенной трассы
        HandlingNe();                           //обработка единых номеров

        HandlingLink();

        UpdateGenTrack();                       //обновлеем обобщенную трассу
    }
}

void Num::HandlingIvo()                     //определяем ИВО результитующей обобщенной трассы
{

    PTPV::air::EUTrcState state = currentTask.GetState();


    if(state == COMMON::_PTPV_::EU_TS_NEW)       //совершенно новая трасса
    {
        //добавляем источник в список ИсточниковИВО
        currentTask.GetMiddleNum()->AddSensorIvo(currentTask.GetInputMsg()->GetNumberSensor());

        //источникИВОрез = источникИВОи
        currentTask.GetMiddleNum()->SetSensorIvo(currentTask.GetInputMsg()->GetNumberSensor());

        //ИВОрез = ИВОи
        currentTask.GetMiddleNum()->SetIvo(currentTask.GetInputMsg()->GetIvo());
    }
    else if(state == COMMON::_PTPV_::EU_TS_END)
    {
        //удаляем источник
        //если источник не единственен в массиве источнков, определяющих ИВО
        if(!(this->currentTask.GetGenTrack()->IsOneMaxRankSIvo()))
        {
            //удаляем источник
            this->currentTask.GetMiddleNum()->DeleteSensorIvo(this->currentTask.GetInputMsg()->GetNumberSensor());

            //если источник был источником являющимся ИсточникомИВО, то назначаем другой источник из оставшихся в массиве за ИсточникИВО соответственно
            if(this->currentTask.GetInputMsg()->GetNumberSensor() == this->currentTask.GetGenTrack()->GetSensorIvo())
            {
                this->currentTask.GetMiddleNum()->SetSensorIvo(this->currentTask.GetMiddleNum()->GetList("ivo")->first());
            }
        }
    }
    else                                           //состояние трассы = ведется
    {
        int rank_o = this->SensorDescription[currentTask.GetGenTrack()->GetSensorIvo()].rank;
        int rank_i = currentTask.GetCurSensor()->rank;

        int ivo_i = currentTask.GetInputMsg()->GetIvo();
        int ivo_o = currentTask.GetGenTrack()->GetIvo();

        //Ранг_о = Ранг_и
        if(rank_o == rank_i)
        {
            //добавляем истоник в список ИсточниковИВО, если он не добавлен
            currentTask.GetMiddleNum()->AddSensorIvo(currentTask.GetInputMsg()->GetNumberSensor());

            //ИсточникИВОрез = ИсточникИВОо
            currentTask.GetMiddleNum()->SetSensorIvo(currentTask.GetGenTrack()->GetSensorIvo());

            //если сообщение пришло от источника, который имеет единоличное право на установку ИВО
            //и его значение ИВО!=НО
            if((currentTask.GetMiddleNum()->IsOneMaxRankIvo()== true) && (ivo_i!=COMMON::EU_IVO_UNKNOWN))
            {
                //ИВОрез = ИВОи
                currentTask.GetMiddleNum()->SetIvo(currentTask.GetInputMsg()->GetIvo());
            }
            //если ИВОо==НО,а ИВОи != НО
            else if((ivo_o==COMMON::EU_IVO_UNKNOWN) && (ivo_i!=COMMON::EU_IVO_UNKNOWN))
            {
                //ИВОрез = ИВОи
                currentTask.GetMiddleNum()->SetIvo(currentTask.GetInputMsg()->GetIvo());
            }
            //если ИВОи==НО
            else if(ivo_i==COMMON::EU_IVO_UNKNOWN)
            {
                //ИВОрез = ИВОо
                currentTask.GetMiddleNum()->SetIvo(currentTask.GetGenTrack()->GetIvo());
            }
            else
            {
                int ivo = this->tableNum.tableIvo->array[currentTask.GetInputMsg()->GetIvo()][currentTask.GetGenTrack()->GetIvo()].first();
                if(ivo!=-1)
                {
                    //определяем ИВОрез по таблице
                    currentTask.GetMiddleNum()->SetIvo(ivo);
                }
                else
                {
                    //присваиваем то, что находится в обобщенной трассе
                    currentTask.GetMiddleNum()->SetIvo(ivo_o);
                }
            }

        }

        ///РАНГИ НЕ РАВНЫ
        //если ИВОо = НО, а ИВОи != НО
        else if((ivo_o==COMMON::EU_IVO_UNKNOWN) && (ivo_i!=COMMON::EU_IVO_UNKNOWN))
        {
            //ИВОрез = ИВОи
            currentTask.GetMiddleNum()->SetIvo(ivo_i);

            //ИсточникИВОрез = ИсточникСообщения
            currentTask.GetMiddleNum()->SetSensorIvo(currentTask.GetInputMsg()->GetNumberSensor());

            //освобождаем список ИсточниковИВО
            currentTask.GetMiddleNum()->FreeSensorLstIvo();

            //добавляем в список ИсточниковИВО ИсточникСообщения
            currentTask.GetMiddleNum()->AddSensorIvo(currentTask.GetInputMsg()->GetNumberSensor());

        }
        //если ИВОо!= НО, а ИВОи=НО
        else if((ivo_o!=COMMON::EU_IVO_UNKNOWN) && (ivo_i==COMMON::EU_IVO_UNKNOWN))
        {
            //ИВОрез = ИВОо
            currentTask.GetMiddleNum()->SetIvo(ivo_o);

            //ИсточникИВОрез = ИсточникИВОо
            currentTask.GetMiddleNum()->SetSensorIvo(currentTask.GetGenTrack()->GetSensorIvo());
        }
        //если Ранг_о < Ранг_и
        else if(rank_o < rank_i)
        {
            //ИВОрез = ИВОи
            currentTask.GetMiddleNum()->SetIvo(ivo_i);

            //ИсточникИВОрез = ИсточникСообщения
            currentTask.GetMiddleNum()->SetSensorIvo(currentTask.GetInputMsg()->GetNumberSensor());

            //освобождаем список ИсточниковИВО
            currentTask.GetMiddleNum()->FreeSensorLstIvo();

            //добавляем в список ИсточниковИВО ИсточникСообщения
            currentTask.GetMiddleNum()->AddSensorIvo(currentTask.GetInputMsg()->GetNumberSensor());
        }
        //если Ранг_о > Ранг_и
        else
        {
            //ИВОрез = ИВОо
            currentTask.GetMiddleNum()->SetIvo(ivo_o);

            //ИсточникИВОрез = ИсточникИВОо
            currentTask.GetMiddleNum()->SetSensorIvo(currentTask.GetGenTrack()->GetSensorIvo());
        }
    }
}


bool Num::HandlingTvo()                     //определяем ТВО результитующей обобщенной трассы
{
    PTPV::air::EUTrcState state = currentTask.GetState();

    if(state == COMMON::_PTPV_::EU_TS_NEW)       //совершенно новая трасса
    {
        //добавляем источник в список ИсточниковТВО
        currentTask.GetMiddleNum()->AddSensorTvo(currentTask.GetInputMsg()->GetNumberSensor());

        //источникТВОрез = источникТВОи
        currentTask.GetMiddleNum()->SetSensorTvo(currentTask.GetInputMsg()->GetNumberSensor());

        //ТВОрез = ТВОи
        currentTask.GetMiddleNum()->SetTvo(currentTask.GetInputMsg()->GetTvo());

    }
    else if(state == COMMON::_PTPV_::EU_TS_END)
    {
        //если источник не единственен в массиве источнков, определяющих ТВО
        if(!(this->currentTask.GetGenTrack()->IsOneMaxRankSTvo()))
        {
            //htmlFile->Write(this->currentTask.GetInputMsg()->GetNumberTrack(),"tvo",this->currentTask.GetInputMsg()->GetNumberSensor());

            //удаляем источник
            this->currentTask.GetMiddleNum()->DeleteSensorTvo(this->currentTask.GetInputMsg()->GetNumberSensor());

            //если источник был источником являющимся ИсточникомТВО, то назначаем другой источник из оставшихся в массиве за ИсточникТВО соответственно
            if(this->currentTask.GetInputMsg()->GetNumberSensor() == this->currentTask.GetGenTrack()->GetSensorTvo())
            {
                this->currentTask.GetMiddleNum()->SetSensorTvo(this->currentTask.GetMiddleNum()->GetList("tvo")->first());
            }
        }
    }
    else        //состояние трассы = ведется
    {
        int rank_o = this->SensorDescription[currentTask.GetGenTrack()->GetSensorTvo()].rank;
        int rank_i = currentTask.GetCurSensor()->rank;

        int tvo_o = currentTask.GetGenTrack()->GetTvo();
        int tvo_i = currentTask.GetInputMsg()->GetTvo();

        //Ранг_о = Ранг_и
        if(rank_o == rank_i)
        {
            //добавляем истоник в список ИсточниковТВО, если он не добавлен
            currentTask.GetMiddleNum()->AddSensorTvo(currentTask.GetInputMsg()->GetNumberSensor());

            //ИсточникТВОрез = ИсточникТВОо
            currentTask.GetMiddleNum()->SetSensorTvo(currentTask.GetGenTrack()->GetSensorTvo());

            //если сообщение пришло от источника, который имеет единоличное право на установку ТВО
            //и ТВОи!=НО
            if((currentTask.GetMiddleNum()->IsOneMaxRankTvo()== true) && (tvo_i!=COMMON::EU_TVO_UNKNOWN))
            {
                //ТВОрез = ТВОи
                currentTask.GetMiddleNum()->SetTvo(currentTask.GetInputMsg()->GetTvo());
            }
            //если ТВОо==НО,а ТВОи != НО
            else if((tvo_o==COMMON::EU_TVO_UNKNOWN) && (tvo_i!=COMMON::EU_TVO_UNKNOWN))
            {
                //ТВОрез = ТВОи
                currentTask.GetMiddleNum()->SetTvo(currentTask.GetInputMsg()->GetTvo());
            }
            //если ТВОи==НО
            else if(tvo_i==COMMON::EU_TVO_UNKNOWN)
            {
                //ТВОрез = ТВОо
                currentTask.GetMiddleNum()->SetTvo(currentTask.GetGenTrack()->GetTvo());
            }
            else
            {

                int elTvoL1_i = tableNum.tableTvo->arrayTvo[tvo_i]->arrayLevelValue[1];
                int elTvoL1_o = tableNum.tableTvo->arrayTvo[tvo_o]->arrayLevelValue[1];


                //если ПервыйУровеньТВОи == ПервыйУровеньТВОо
                if(elTvoL1_i == elTvoL1_o)
                {
                    //можем объединить
                    int n = (tableNum.tableTvo->arrayTvo[tvo_i]->numberCurrentLevel > tableNum.tableTvo->arrayTvo[tvo_o]->numberCurrentLevel) ? tableNum.tableTvo->arrayTvo[tvo_o]->numberCurrentLevel : tableNum.tableTvo->arrayTvo[tvo_i]->numberCurrentLevel;
                    int new_tvo;

                    //ищем наивысший общий уровень, значение ТВО этого общего уровня - ТВОрез
                    for(int i=n;i>0;i--)
                    {
                        if(tableNum.tableTvo->arrayTvo[tvo_i]->arrayLevelValue[i] == tableNum.tableTvo->arrayTvo[tvo_o]->arrayLevelValue[i])
                        {
                            new_tvo = tableNum.tableTvo->arrayTvo[tvo_i]->arrayLevelValue[i];
                            break;
                        }
                    }


                    //устанавливаем ТВОрез
                    currentTask.GetMiddleNum()->SetTvo(new_tvo);
                }
                //прямое объединение не удалось провести
                else
                {
                    int threat_i = GetThreatTvo(elTvoL1_i);
                    int threat_o = GetThreatTvo(elTvoL1_o);

                    if(threat_i > threat_o)
                    {
                        currentTask.GetMiddleNum()->SetTvo(elTvoL1_i);
                    }
                    else if(threat_i < threat_o)
                    {
                        currentTask.GetMiddleNum()->SetTvo(elTvoL1_o);
                    }
                }
            }
        }
        ///РАНГИ НЕ РАВНЫ
        //если ТВОо = НО, а ТВОи != НО
        else if((tvo_o==COMMON::EU_TVO_UNKNOWN) && (tvo_i!=COMMON::EU_TVO_UNKNOWN))
        {
            //ТВОрез = ТВОи
            currentTask.GetMiddleNum()->SetTvo(tvo_i);

            //ИсточникТВОрез = ИсточникСообщения
            currentTask.GetMiddleNum()->SetSensorTvo(currentTask.GetInputMsg()->GetNumberSensor());

            //освобождаем список ИсточниковТВО
            currentTask.GetMiddleNum()->FreeSensorLstTvo();

            //добавляем в список ИсточниковТВО ИсточникСообщения
            currentTask.GetMiddleNum()->AddSensorTvo(currentTask.GetInputMsg()->GetNumberSensor());

        }
        //если ТВОо!= НО, а ТВОи=НО
        else if((tvo_o!=COMMON::EU_TVO_UNKNOWN) && (tvo_i==COMMON::EU_TVO_UNKNOWN))
        {
            //ТВОрез = ТВОо
            currentTask.GetMiddleNum()->SetTvo(tvo_o);

            //ИсточникТВОрез = ИсточникТВОо
            currentTask.GetMiddleNum()->SetSensorTvo(currentTask.GetGenTrack()->GetSensorTvo());
        }
        //если Ранг_о < Ранг_и
        else if(rank_o < rank_i)
        {
            //ТВОрез = ТВОи
            currentTask.GetMiddleNum()->SetTvo(tvo_i);

            //ИсточникТВОрез = ИсточникСообщения
            currentTask.GetMiddleNum()->SetSensorTvo(currentTask.GetInputMsg()->GetNumberSensor());

            //освобождаем список ИсточниковТВО
            currentTask.GetMiddleNum()->FreeSensorLstTvo();

            //добавляем в список ИсточниковТВО ИсточникСообщения
            currentTask.GetMiddleNum()->AddSensorTvo(currentTask.GetInputMsg()->GetNumberSensor());
        }
        //если Ранг_о > Ранг_и
        else
        {
            //ТВОрез = ТВОо
            currentTask.GetMiddleNum()->SetTvo(tvo_o);

            //ИсточникТВОрез = ИсточникТВОо
            currentTask.GetMiddleNum()->SetSensorTvo(currentTask.GetGenTrack()->GetSensorTvo());
        }
    }

    return true;
}

int Num::GetThreatTvo(int tvoLevelOne)          //определение уровня угрозы ТВО
{
    return tvoLevelOne;
//    switch(tvo)
//    {
//    case N_U_M::NUM_TVO_RT:
//        return 3;
//    case COMMON::EU_TVO_HS_AIRCRAFT:
//        return 1;                       //самый опасный
//    case N_U_M::NUM_TVO_PN:
//        return 4;
//    case N_U_M::NUM_TVO_CA:
//        return 2;
//    default:
//        qDebug()<<"ERROR";
//        return -1;
//    }
}

void Num::HandlingNe()                      //определяем Ne результитующей обобщенной трассы
{

    int ne_msg = currentTask.GetInputMsg()->GetNe();            //Ne из сообщения
    int ne_gen = currentTask.GetGenTrack()->GetNe();

    PTPV::air::EUTrcState state = currentTask.GetState();


    if(state==COMMON::_PTPV_::EU_TS_NEW)
    {
        currentTask.GetMiddleNum()->SetNe(ne_msg);
    }
    else
    {
        if(ne_msg!= 0)
        {
            if(ne_gen == 0)
            {
                currentTask.GetMiddleNum()->SetNe(ne_msg);
            }
            else
            {
                currentTask.GetMiddleNum()->SetNe(ne_gen);
            }
        }
    }

}

void Num::HandlingLink()
{
    //ИО

    int curIO = COMMON::EU_IVO_UNKNOWN;
    bool stateIO = true;

    if(currentTask.GetMiddleNum()->IsOneMaxRankIvo() == false)
    {
        QList<int>* lstIO = currentTask.GetMiddleNum()->GetList("ivo");

        QList<int>::iterator it = lstIO->begin();

        while (it != lstIO->end())
        {
            int sensNum = *it;

            int numberTrcOnNumerationSensor = (*(this->aTrc))[currentTask.GetInputMsg()->GetNumberTrack()].genTrc.sensTrcNum[sensNum];
            PTPV::air::TSensGenTrcLink * curLink = &Link[sensNum][numberTrcOnNumerationSensor];

            if(curLink->identState!=0)
            {
                if(curLink->Data->IO!=COMMON::EU_IVO_UNKNOWN)
                {
                    if(curIO == COMMON::EU_IVO_UNKNOWN)
                    {
                        curIO = curLink->Data->IO;
                    }
                    else
                    {
                        if(curIO != curLink->Data->IO)
                        {
                            stateIO = false;
                            break;
                        }
                    }
                }
            }

            ++it;
        }
    }
    else
    {
        stateIO = false;
    }


    if((stateIO == true) && (curIO != COMMON::EU_IVO_UNKNOWN))
    {
        currentTask.GetMiddleNum()->SetIvo(curIO);
    }


    //ТО

    int curTO = COMMON::EU_TVO_UNKNOWN;
    bool stateTO = true;

    if(currentTask.GetMiddleNum()->IsOneMaxRankTvo() == false)
    {
        QList<int>* lstTO = currentTask.GetMiddleNum()->GetList("tvo");
        QList<int>::iterator it = lstTO->begin();

        while (it != lstTO->end())
        {
            int sensNum = *it;

            int numberTrcOnNumerationSensor = (*(this->aTrc))[currentTask.GetInputMsg()->GetNumberTrack()].genTrc.sensTrcNum[sensNum];
            PTPV::air::TSensGenTrcLink * curLink = &Link[sensNum][numberTrcOnNumerationSensor];

            if(curLink->identState!=0)
            {
                if(curLink->Data->TO!=COMMON::EU_TVO_UNKNOWN)
                {
                    if(curTO == COMMON::EU_TVO_UNKNOWN)
                    {
                        curTO = curLink->Data->TO;
                    }
                    else
                    {
                        if(curTO != curLink->Data->TO)
                        {
                            stateTO = false;
                            break;
                        }
                    }
                }
            }

            ++it;
        }
    }
    else
    {
        stateTO = false;
    }


    if((stateTO == true) && (curTO != COMMON::EU_TVO_UNKNOWN))
    {
        currentTask.GetMiddleNum()->SetTvo(curTO);
    }


    //Ne

    int curNe = 0;
    bool stateNe = true;

    if(currentTask.GetMiddleNum()->IsOneMaxRankIvo() == false)
    {
        QList<int>* lstIO = currentTask.GetMiddleNum()->GetList("ivo");
        QList<int>::iterator it = lstIO->begin();

        while (it != lstIO->end())
        {
            int sensNum = *it;

            int numberTrcOnNumerationSensor = (*(this->aTrc))[currentTask.GetInputMsg()->GetNumberTrack()].genTrc.sensTrcNum[sensNum];

            if(numberTrcOnNumerationSensor == 0)
            {
                stateNe = false;
                break;
            }
            else
            {
                PTPV::air::TSensGenTrcLink * curLink = &Link[sensNum][numberTrcOnNumerationSensor];

                if(curLink->identState!=0)
                {
                    if(curLink->Data->uniNum!=0)
                    {
                        if(curNe == 0)
                        {
                            curNe = curLink->Data->uniNum;
                        }
                        else
                        {
                            if(curNe != curLink->Data->uniNum)
                            {
                                stateNe = false;
                                break;
                            }
                        }
                    }
                }
            }

            ++it;
        }
    }
    else
    {
        stateNe = false;
    }


    if((stateNe == true) && (curNe != 0))
    {
        currentTask.GetMiddleNum()->SetNe(curNe);
    }
}


void Num::UpdateGenTrack()                          //обновляем обобщенную трассу в соостветсвии с результатом обработки  принятого сообщения
{
    GenTrack* gt = this->currentTask.GetGenTrack();
    TrackNum* en = this->currentTask.GetMiddleNum();

    gt->SetIvo(en->GetIvo());
    gt->SetSensorIvo(en->GetSensorIvo());

    gt->SetTvo(en->GetTvo());
    gt->SetSensorTvo(en->GetSensorTvo());

    gt->SetNe(en->GetNe());

    CopyListsOut();
}

///вызов диспетчера задач процесса нумерации и индексации по периодическим ситуациям
void Num::StateTaskChain(PTPV::air::TStateProc *pStateProc)                      /*явный вызов переменных структуры pStateProc (!!!) */
{
    //если трасса сбрасывается
    if(pStateProc->genTrcDrop == 1)
    {
        aTrcNum[pStateProc->genTrcNum].FreeSensorLstIvo();
        aTrcNum[pStateProc->genTrcNum].FreeSensorLstTvo();

    }
    //если сбрасывается источник
    else if(pStateProc->sensTrcDrop == 1)
    {
        //у нас нет монополии на присвоение ИВО и ТВО
        if(!(aTrcNum[pStateProc->genTrcNum].IsOneMaxRankIvo() && aTrcNum[pStateProc->genTrcNum].IsOneMaxRankTvo()))
        {
            for(int i=0;i<COMMON::SENS_MAX+1;i++)
            {
                //если данный источник сбрасывается
                if(pStateProc->sensTrcDelete[i] == 1)
                {
                    //если у нас нет монополия на ИВО
                    if(!(aTrcNum[pStateProc->genTrcNum].IsOneMaxRankIvo()))
                    {
                        //удаляем источник  из списка ИсточниковИВО
                        aTrcNum[pStateProc->genTrcNum].DeleteSensorIvo(i);
                        //если его номер был номером ИсточникаИВО, то заменяем другим из списка ИсточниковИВО (первым из массива)
                        if(i == aTrcNum[pStateProc->genTrcNum].GetSensorIvo())
                        {
                            aTrcNum[pStateProc->genTrcNum].SetSensorIvo(aTrcNum[pStateProc->genTrcNum].GetList("ivo")->first());
                        }
                    }
                    //если у нас нет монополия на ТВО
                    if(!(aTrcNum[pStateProc->genTrcNum].IsOneMaxRankTvo()))
                    {
                        //удаляем источник  из списка ИсточниковТВО
                        aTrcNum[pStateProc->genTrcNum].DeleteSensorTvo(i);
                        //если его номер был номером ИсточникаТВО, то заменяем другим из списка ИсточниковТВО (первым из массива)
                        if(i == aTrcNum[pStateProc->genTrcNum].GetSensorTvo())
                        {
                            aTrcNum[pStateProc->genTrcNum].SetSensorTvo(aTrcNum[pStateProc->genTrcNum].GetList("tvo")->first());
                        }
                    }
                }
            }
        }
    }
}


void Num::CopyListsIn()                         //копирование массивов источников ИВО и ТВО из обобщенной трассы в текущую результирующую
{
    //очищаем
    currentTask.GetMiddleNum()->FreeSensorLstIvo();
    currentTask.GetMiddleNum()->FreeSensorLstTvo();

    //копируем
    for(int i=0;i<currentTask.GetGenTrack()->GetList("ivo")->count();i++)
    {
        currentTask.GetMiddleNum()->AddSensorIvo(currentTask.GetGenTrack()->GetList("ivo")->at(i));
    }


    for(int i=0;i<currentTask.GetGenTrack()->GetList("tvo")->count();i++)
    {
        currentTask.GetMiddleNum()->AddSensorTvo(currentTask.GetGenTrack()->GetList("tvo")->at(i));
    }
}

void Num::CopyListsOut()                    //копирование массивов источников ИВО и ТВО из текущей результирующей в обобщенную трассу
{
    //очищаем
    currentTask.GetGenTrack()->FreeSensorLstIvo();;
    currentTask.GetGenTrack()->FreeSensorLstTvo();

    //копируем
    for(int i=0;i<currentTask.GetMiddleNum()->GetList("ivo")->count();i++)
    {
        currentTask.GetGenTrack()->AddSensorIvo(currentTask.GetMiddleNum()->GetList("ivo")->at(i));
    }


    for(int i=0;i<currentTask.GetMiddleNum()->GetList("tvo")->count();i++)
    {
        currentTask.GetGenTrack()->AddSensorTvo(currentTask.GetMiddleNum()->GetList("tvo")->at(i));
    }
}


}
