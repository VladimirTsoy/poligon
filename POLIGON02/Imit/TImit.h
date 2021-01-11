//  класс TImit   //h
#ifndef TIMIT_H
#define TIMIT_H

#include "_IMIT_.h"
#include "DefImit.h"
#include "HImit.h"
#include "Sens.h"

namespace imit
{
using namespace COMMON::_IMIT_;

class TImit
{
private:


    unsigned int NextRecord[TRACK_MAX];
    unsigned int firstRecord;
    unsigned int lastRecord;

    TEtalon Etalon[TRACK_MAX];

//    TObjectContr ObjectContr[TRACK_MAX+1];
    TObjectContr * ObjectContr;

public:
    Sens *sens;
    TDinChar DinChar;

    TMsgTrc MsgTrc[CountMessage_MAX];

    TPubEtalon PubEtalon[TRACK_MAX];
    static TPubEtalon CPubEtalon0;

    int ImitAir(double currentT);  /* имитация эталона */


    /************************************/

    void AssayTrack(TEtalon* pEtalon,TPubEtalon* pPubEtalon,double currentT); /*анализ эталона*/
    void Extr(TEtalon* pEtalon,TPubEtalon* pPubEtalon,double dt);   /*экстраполяция эталона */
    void Reference(TEtalon* pEtalon,TPubEtalon* pPubEtalon);   /*сдвиг опорной точки к началу очередного изменения параметров движения*/
    void ObjectStart(double currentT); /*вызов контрольной задачи*/
    void EtalEnd(TEtalon* pEtalon,TPubEtalon* pPubEtalon,unsigned int numEt);                     //стирание(сброс) ЭВО
    void EtalDrop(TEtalon* pEtalon,TPubEtalon* pPubEtalon,unsigned int numEt);                                             /* стирание эталонов (1 эталона)*/
    void RecordMan(TEtalon* pEtalon,unsigned int numMan);                     // запись маневра ЭО
    void Init(void);                                       // инициализация переменных информационных модулей
    unsigned int CreatRecord(void);        // занятие формуляра
    void DestroyRecord(unsigned int namberTrack);        // освобождение формуляра

    TMsgTrc* getMsgTrc(int number);
    TPubEtalon* getPubEtalon(int number);

    TImit(TObjectContr * _t_object_contr, TCharSens * _t_char_sens, TSensSite * _t_sens_site);
   ~TImit();

};

} // namespace imit

#endif /* TIMIT_H */
