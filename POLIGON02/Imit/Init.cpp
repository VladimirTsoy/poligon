#include "Init.h"

namespace BIUS_A100
{

Init::Init()
{
}

Init::~Init()
{
}

void Init::traverseDinChar(TDinChar *_dinChar, int _real_k)
{
    _dinChar->regimeImit = true;      // Включение режима имитации,YES- включена имитация
    _dinChar->realTime = true;        // Режим реального времени (YES-включен)
    _dinChar->zoneView = true;        //зона вимости расширена
    _dinChar->countRecord = 0;         // Количество занятых формуляров                           [KZF]
    _dinChar->countLibertyRecord = 500; // Количество свободных формуляров                         [KSF]
    _dinChar->countContr = _real_k;          /// Количество эталонов в контрольной задаче
    _dinChar->objectContr = 1;          /// 1 - включение режима контрольной задачи
}

}
