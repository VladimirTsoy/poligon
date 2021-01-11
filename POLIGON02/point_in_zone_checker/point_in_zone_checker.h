#ifndef POINT_IN_ZONE_CHECKER_H
#define POINT_IN_ZONE_CHECKER_H

#include "../CSCommon/include/UZone.h"

using namespace std;

using namespace COMMON;
using namespace COMMON::_ZONE_;
using namespace std;

// класс обеспечивает проверку признака принадлежности точки зонам
class point_in_zone_checker
{
public:
    // конструктор
    point_in_zone_checker();

    // деструктор
    ~point_in_zone_checker();

    // вернуть признаки принадлежности точки зонам
    void ret_b_point_in_zone(int _point_x, int _point_y, bool * _b_res);

    TZone * ret_Zone();           // вернуть массив зоны
    int ret_zone_real_count();    // вернуть реальное количество зон
    void set_Zone(TZone * _Zone); // установить массив зоны
    void set_zone_real_count();   // установить реальное количество зон

private:
    TZone Zone[ZONE_MAX];         // массив зоны
    int zone_real_count;          // реальное количество зон
};

#endif // POINT_IN_ZONE_CHECKER_H
