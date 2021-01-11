#include "string.h"
#include "Init.h" // временно
#include "HImit.h"
#include "TImit.h"
#include <QDebug>
namespace imit
{
using namespace  BIUS_A100; // временно

TPubEtalon  TImit:: CPubEtalon0;

TImit::TImit(TObjectContr * _t_object_contr,
             TCharSens * _t_char_sens,
             TSensSite * _t_sens_site)
{
    qDebug()<<"Start tImit";

    sens = new Sens(&DinChar, MsgTrc, PubEtalon, _t_char_sens, _t_sens_site);

    int recordSize;

    /// Создание зоны характеристик эталонов
    recordSize = sizeof(TEtalon) * TRACK_MAX;
    memset(&Etalon, 0, recordSize);

    /// Создание зоны характеристик эталонов
    recordSize = sizeof(TPubEtalon) * TRACK_MAX;
    memset(&PubEtalon, 0, recordSize);
    for(int i = 1; i < TRACK_MAX; ++i)
    {
        /// Чистка зоны эталонов
        PubEtalon[i] = CPubEtalon0;
    }

    ObjectContr = _t_object_contr;

    int real_k;
    real_k = 0;
    for(int i=0; i<TRACK_MAX; i++)
    {
        if(_t_object_contr[i].trackBZ == true)
        {
            real_k++;
        }
    }

    recordSize = sizeof(TDinChar);
    memset(&DinChar, 0, recordSize);
    Init::traverseDinChar(&DinChar, real_k);
}

TImit::~TImit()
{
    delete sens;
}

void TImit :: Init(void)                  //формирования начальных значений цепочки адресов
{
    int i;
    NextRecord[0] = 0;
    NextRecord[1] = 0;
    for ( i=1 ; i<TRACK_MAX ; i++ )
        NextRecord[i] = i+1;
    NextRecord[TRACK_MAX] = 0;
    firstRecord = 1;
    lastRecord = TRACK_MAX;
}

/// Занятие формуляра
unsigned int TImit :: CreatRecord(void)
{
    int num;
    if ( firstRecord!= 0)
    {
        num = firstRecord;
        firstRecord = NextRecord[num];
        NextRecord[num] = 0;
        if ( firstRecord== 0)
            lastRecord=0;
        return num;
    }
    else
        return 0;
}

/// Освобождение формуляра
void TImit :: DestroyRecord(unsigned int numEt)
{
    if(firstRecord==0)
    {
        firstRecord=numEt;
        lastRecord=numEt;
    }
    else
    {
        NextRecord[lastRecord]=numEt;
        lastRecord=numEt;
    }
}

TMsgTrc* TImit::getMsgTrc(int number)
{
    return &MsgTrc[number];
}

TPubEtalon*
TImit::getPubEtalon(int number)
{
    return &PubEtalon[number];
}


void TImit::ObjectStart(double currentT)
{

    double T,dte;
    double dt=0.05;                           //константа разноса по времени выдачи трасс в 10с цикле
    unsigned int numEt,num,man,i;
 //   int drop;
    TEtalon* pEtalon;
    TObjectContr* pObjectContr;
    TPubEtalon* pPubEtalon;
    Init();                                              //формирования начальных значений цепочки адресов
    if(DinChar.objectContr == 1)                               //запись КЗ
    {
            if((DinChar.regimeImit == true)&&(DinChar.realTime==true))
                T=currentT;                                          //имитация включена, запоминание текущего времени
            qDebug() << "T = "<<T;
//             qDebug()<< "DinChar.countContr = "<<DinChar.countContr;

            for(num = 1; num <= DinChar.countContr; num++)           //начало цикла по зоне КЗ
            {
                  pObjectContr = ObjectContr;
                   pObjectContr = pObjectContr+num;
                if (pObjectContr->trackBZ == true )                 //формуляр занят
                {
                    qDebug()<<"start_track_bz";

                    // поиск свободного места
                    numEt = CreatRecord();
                     pEtalon = Etalon;
                    pPubEtalon = PubEtalon;
                    pEtalon = pEtalon + numEt;
                    pPubEtalon = pPubEtalon + numEt;
                    DinChar.countRecord++;           //увеличение количества занятых формуляров
                    DinChar.countLibertyRecord--;     // уменьшение количества свободных формуляров
                    pEtalon->trackBZ = true;                     // формуляр занят  (YES-занят)
                    pEtalon->psiReference = pPubEtalon->psi = pObjectContr->psi;          // курс объекта
                    pEtalon->xReference = pPubEtalon->x = pObjectContr->x;             // коорд
                    pEtalon->yReference = pPubEtalon->y = pObjectContr->y;             // коорд
                    pEtalon->hReference = pPubEtalon->h = pObjectContr->h;             // высота
                    pEtalon->vReference = pPubEtalon->v = pObjectContr->v;             // скорость объекта
                    pEtalon->vxReference = pPubEtalon->vx = pObjectContr->v * cos(pObjectContr->psi);        //Vx=Vо*cosQо; скорость объекта
                    pEtalon->vyReference = pPubEtalon->vy = pObjectContr->v * sin(pObjectContr->psi);                    //Vy=V*sinQ;             // скорость объекта
                    pEtalon->vh = pPubEtalon->vh = pObjectContr->vh;             // скорость по высоте
                    pEtalon->countManevr = pObjectContr-> countManevr;                    // количество маневров
                    pEtalon->ObjClass = pPubEtalon->ObjClass = pObjectContr->ObjClass;                     // тип трассы
                    pPubEtalon->OGP = pObjectContr->OGP;
                    pEtalon->IO = pPubEtalon->IO = pObjectContr->IO;
                    pEtalon->TO = pPubEtalon->TO = pObjectContr->TO;
                    pPubEtalon->vx = pPubEtalon->v * cos(pPubEtalon->psi);
                    pPubEtalon->vy = pPubEtalon->v * sin(pPubEtalon->psi);
                    dte = T + dt * num;                                          //разнос по времени в 10с цикле
                    pEtalon->tStart = pEtalon->tStartMovem = pEtalon->tExtr = pObjectContr->tStart + dte;    // Время начала имитации объекта  [TH], последней экстраполяции координат[T]
                     pEtalon->tFinish = pObjectContr->tFinish+dte;                // Время окончания имитации объекта [TK]
                    pEtalon->tNextExtr = 0;                                       // время следующей экстраполяции координат
                    for(  i = 0; i < SENS_MAX; ++i)                                    //разнос по времени выдачи источников информации
                      pEtalon->tNextGivSens[i] = pEtalon->tStart + i;
                    if(T != 0)                 //имитация включена
                     pEtalon->trackEnd = 0;              //признак конца трассы
                    if(pEtalon->countManevr == 0)                 //нет маневра
                        pEtalon->tMovem = 0;                 // время очередного изменения движения [TKM]
                    else                                     //запись маневров
                    {
                        pEtalon->tMovem = pObjectContr->Manevr[1].tStart + dte;  //время конца маневра =времени начала следующего маневра
                        for(man = 1;man <= pEtalon->countManevr;man++)           //начало цикла по маневрам
                        {
                            pEtalon->Manevr[man].tStart = pObjectContr->Manevr[man].tStart + dte;  //время конца маневра =времени начала следующего маневра
                            pEtalon->Manevr[man].tFinish = pObjectContr->Manevr[man].tFinish + dte;
                            pEtalon->Manevr[man].vh = pObjectContr->Manevr[man].vh;
                            pEtalon->Manevr[man].a =  pObjectContr->Manevr[man].a;
                            pEtalon->Manevr[man].r = pObjectContr->Manevr[man].r;
                         }
                    }
                }
            }                          //конец цикла по КЗ}
       //}
      }// return ;
   }

int TImit::ImitAir(double currentT)
{
    short int numEt;
    char racp;
    static TEtalon* pEtalon;
    static TPubEtalon* pPubEtalon;
    if( DinChar.regimeImit ==  true)
    {
        DinChar.countMessage = 0;                        //0->количество сообщений
        for(numEt = 1;numEt < TRACK_MAX;numEt++)
        {
            pEtalon = Etalon;
            pEtalon = pEtalon + numEt;
            pPubEtalon = PubEtalon;
            pPubEtalon = pPubEtalon + numEt;
            racp = 0;
            if (pEtalon->trackBZ == true)                 //ВО включен в имитацию
            {
                if (pEtalon->trackEnd == true)                //признак конца трассы
                  {
                    EtalEnd(pEtalon,pPubEtalon,numEt);                    //стирание(сброс) ЭВО
                    continue;
                   }
                // проверка времени существования эталона
                if((currentT < pEtalon->tStart))                 //текущее время< времени начала трассы
                    continue;
               if(pEtalon->tNextExtr <= currentT)        //подошло ли время следующей экстраполяции
                {
                    pPubEtalon->visual = true;                 //признак отображения
                    if(currentT >= pEtalon->tFinish)                 //текущее время> времени конца трассы
                    {
                         if(++pEtalon->meterEndTrack <= END_TRACK_MAX)
                            racp = 2;                                              // ЭКСТРАПОЛЯЦИЯ
                        else      //количество обзоров больше 7
                        {
                            racp = 3;                                        //конец трассы после 7 обзоров, СБРОС
                            sens->AssaySens(pPubEtalon,pEtalon,numEt,racp,currentT);       /*анализ источников сопровождения данной трассы*/
//                            EtalEnd(pEtalon,pPubEtalon,numEt);                   //стирание(сброс) ЭВО
                            pEtalon->trackEnd = true;                                   //признак конца трассы
                            continue;                                             //на конец цикла
                        }
                    }
                    AssayTrack(pEtalon,pPubEtalon,currentT);                  /*анализ эталона*/
                   if((pEtalon->ObjClass == 1)&&(pPubEtalon->h <= 1))
                        racp = 3;                                        //конец трассы , СБРОС
                    sens->AssaySens(pPubEtalon,pEtalon,numEt,racp,currentT);       /*анализ источников сопровождения данной трассы*/
                   }
                if(racp == 3)                                        //конец трассы , СБРОС
                      pEtalon->trackEnd = true;                                   //признак конца трассы
            }
        }
    }
    pEtalon = NULL;
    pPubEtalon = NULL;
//    qDebug() << "!!!";
    return DinChar.countMessage;
}

/// Анализ эталона
void TImit:: AssayTrack(TEtalon* pEtalon,TPubEtalon* pPubEtalon,double currentT)
{
    double tCycl,dt,tkm;
    char numMan;
         tCycl = 1.;                                                  //экстраполяция 1раз в 10с
    if(pEtalon->countManevr == 0)                                //   количество маневров =0
    {
        dt = currentT - pEtalon->tStartMovem;                     //Ттек-ТН
         Extr(pEtalon, pPubEtalon,dt);                           /*экстраполяция эталона */
    }
    else                                                          //ЭВО с маневром
    {
       while(pEtalon->numberManevr < pEtalon->countManevr)      // количество маневров не равно текущему № маневра
        {
             if(pEtalon->tMovem > currentT)                          //время очер изм движ(ТКМ)> текущего
            {
                dt = currentT - pEtalon->tStartMovem;                    //Ттек-ТН
                Extr(pEtalon, pPubEtalon,dt);                          /*экстраполяция эталона */
               goto C ;
            }
            else                                                    //время конца маневра < таймера
            {
                dt = pEtalon->tMovem - pEtalon->tStartMovem;              //ТКМ-ТН
                Extr(pEtalon, pPubEtalon,dt);                          /*экстраполяция эталона */
                Reference(pEtalon, pPubEtalon); //сдвиг опорной точки к началу очередного изменения параметров движения
                tkm = pEtalon->tMovem;
                if(pEtalon->tMovem == pEtalon->Manevr[pEtalon->numberManevr + 1].tStart)  //время конца маневра =времени начала следующего маневра
                {
                    numMan = ++pEtalon->numberManevr;
                     RecordMan(pEtalon,numMan);                    //перепись маневра
                }
                else        // участок прямолинейной экстраполяции между маневрами
                {
                    pEtalon->tMovem = pEtalon->Manevr[pEtalon->numberManevr + 1].tStart;          //ТКМ=Тначала след маневра
                    pEtalon->tStartMovem = tkm;                                                   //
                    pEtalon->a = pEtalon->vh = pEtalon->r = 0;
                }
            }
        }                                                            //конец цикла while
        if(pEtalon->tMovem > currentT)                               //время очер изм движ(ТКМ)> текущего
        {
            dt = currentT - pEtalon->tStartMovem;
            Extr(pEtalon, pPubEtalon,dt);                    /*экстраполяция эталона */
        }
        else                                                          //время очер изм движ(ТКМ)<= текущего
        {
            dt = pEtalon->tMovem - pEtalon->tStartMovem;
            Extr(pEtalon, pPubEtalon,dt);                           /*экстраполяция эталона */
            pEtalon->a = pEtalon->vh = pEtalon->r = 0;                 //до конца  прямолинейная экстраполяция
            pEtalon->countManevr = 0;
            Reference(pEtalon, pPubEtalon);                       //сдвиг опорной точки к началу очередного изменения параметров движения
            pEtalon->tStartMovem = pEtalon->tMovem;                   //ТН=ТKM
                if(pEtalon->tStartMovem != currentT)                     //время нач очер изм движ= текущему
                {
                    dt = currentT - pEtalon->tStartMovem;
                    Extr(pEtalon, pPubEtalon,dt);                    /*экстраполяция эталона */
                }
         }
    }
    C:
    pEtalon->tExtr = currentT;
    pEtalon->tNextExtr = currentT+tCycl;
}


/// Экстраполяция эталона
/** **********************************/
void TImit:: Extr(TEtalon* pEtalon, TPubEtalon* pPubEtalon,double dt)
{
     pPubEtalon->manevr = false;                  // Признак наличия маневра (YES - есть маневр)
     if(pEtalon->vh != 0)                        //анализ маневра по высоте и не БТ
        {
            pPubEtalon->h = pEtalon->hReference + pEtalon->vh * dt;  //H=Hi+Vh*dt
            pPubEtalon->vh = pEtalon->vh;
            if(pPubEtalon->h <= 0)
                pPubEtalon->h = 1;
            pPubEtalon->manevr = true;                  // Признак наличия маневра (YES - есть маневр)
        }
    if(pEtalon->a != 0)                          //анализ маневра по скорости
    {
        pPubEtalon->v = pEtalon->vReference + pEtalon->a * dt;   //V=Vi+A*dt
        if(pPubEtalon->v == 0)
            pPubEtalon->v = 1;
        pPubEtalon->manevr = true;                 // Признак наличия маневра (YES - есть маневр)
    }
    if(pEtalon->r != 0)                       //анализ маневра по курсу
    {
        pPubEtalon->psi = pEtalon->psiReference + pPubEtalon->v / pEtalon->r * dt;   //Q=Qо+V/R*dt
        if(pPubEtalon->psi >= 2*M_PI)                                        //>=360град
            pPubEtalon->psi = pPubEtalon->psi - 2*M_PI;
        pPubEtalon->vx = pPubEtalon->v * cos(pPubEtalon->psi);                   //Vx=V*cosQ
        pPubEtalon->vy = pPubEtalon->v * sin(pPubEtalon->psi);                    //Vy=V*sinQ
        pPubEtalon->x = pEtalon->xReference + pEtalon->r * (sin(pPubEtalon->psi) - sin(pEtalon->psiReference));             //X=Xо+R(sinQ-sinQо)
        pPubEtalon->y = pEtalon->yReference + pEtalon->r * (cos(pEtalon->psiReference) - cos(pPubEtalon->psi));             //Y=Yо+R(cosQо-cosQ)
        pPubEtalon->manevr = true;                                                // Признак наличия маневра (YES - есть маневр)

//                      qDebug() << "PSI " << pPubEtalon->psi;
//                      qDebug() << "X " << pPubEtalon->x;
//                       qDebug() << "Y " << pPubEtalon->y;
    }
    else                                           //нет маневра по курсу, прямолинейный участок
    {
        pPubEtalon->vx = (pEtalon->vReference + pEtalon->a * dt) * cos(pEtalon->psiReference);        //Vx=Vо*cosQо
        if(pPubEtalon->vx == 0)
            pPubEtalon->vx = 1;
        pPubEtalon->vy = (pEtalon->vReference + pEtalon->a * dt) * sin(pEtalon->psiReference);        //Vy=Vо*sinQо
        if(pPubEtalon->vy == 0)
            pPubEtalon->vy = 1;
        pPubEtalon->x = pEtalon->xReference + ((pEtalon->vxReference + pPubEtalon->vx) / 2) * dt;                  //X=Xо+((Vox+Vx)/2)*dt
        pPubEtalon->y = pEtalon->yReference + ((pEtalon->vyReference + pPubEtalon->vy) / 2) * dt;                  //Y=Yо+((voy+Vy)/2)*dt
    }
 }

void TImit:: Reference(TEtalon* pEtalon,TPubEtalon* pPubEtalon)   /*сдвиг опорной точки к началу очередного изменения параметров движения*/
{
     pEtalon->xReference = pPubEtalon->x;
     pEtalon->yReference = pPubEtalon->y;
     pEtalon->hReference = pPubEtalon->h;
     pEtalon->psiReference = pPubEtalon->psi;
     pEtalon->vReference = pPubEtalon->v;
     pEtalon->vxReference = pPubEtalon->v*cos(pPubEtalon->psi);        //Vx=Vо*cosQо; скорость объекта
     pEtalon->vyReference = pPubEtalon->v*sin(pPubEtalon->psi);                    //Vy=V*sinQ;             // скорость объект
}


 /// Стирание (сброс) ЭВО
 void TImit::EtalEnd(TEtalon* pEtalon,TPubEtalon* pPubEtalon,unsigned int numEt) /*стирание формуляра*/
 {
     int recordSize;
     DestroyRecord( numEt);
      recordSize = sizeof (TEtalon);
     memset(pEtalon,0,recordSize);
     recordSize = sizeof (TPubEtalon);
     memset(pPubEtalon,0,recordSize);
     DinChar.countRecord--;           //уменьшение количества занятых формуляров
     DinChar.countLibertyRecord++;     // увеличение количества свободных формуляров
  }

 // запись маневра ЭО
 //****************************************************************************************************/
 void TImit::RecordMan(TEtalon* pEtalon,unsigned int numMan)
 {
     pEtalon->tStartMovem = pEtalon->Manevr[numMan].tStart;   //ТН=Тначала след маневра
     pEtalon->tMovem = pEtalon->Manevr[numMan].tFinish;       //ТКМ=Тконца маневра
     pEtalon->vh = pEtalon->Manevr[numMan].vh;
     pEtalon->a = pEtalon->Manevr[numMan].a;
     pEtalon->r = pEtalon->Manevr[numMan].r;
  }

} // namespace imit
