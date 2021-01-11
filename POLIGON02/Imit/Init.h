#ifndef INIT_H
#define INIT_H

#include <QtXml>

#include "_IMIT_.h"
#include "DefImit.h"
#include "Sens.h"

namespace BIUS_A100
{
using namespace COMMON::_IMIT_;

class Init
{
public:
    Init();
    ~Init();

    static void traverseDinChar(TDinChar *_dinChar, int _real_k);
};

}

#endif /* INIT_H */
