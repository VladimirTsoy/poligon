
#ifndef UZONE_H
#define UZONE_H

#include "U.h"

namespace COMMON
{

namespace _ZONE_
{

struct TZone
{
    int r;
    int g;
    int b;
    int a;
    unsigned char countPoint;
    struct TPoint
    {
        int x;
        int y;
    } Point[10];
};


} // namespace _ZONE_

} // namespace COMMON

#endif // UZONE_H
