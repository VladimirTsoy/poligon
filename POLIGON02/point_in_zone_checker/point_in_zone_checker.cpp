#include "point_in_zone_checker.h"

// https://rosettacode.org/wiki/Ray-casting_algorithm#C.2B.2B

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct { double x, y; } vec;
typedef struct { int n; vec* v; } polygon_t, *polygon;

#define BIN_V(op, xx, yy) vec v##op(vec a,vec b){vec c;c.x=xx;c.y=yy;return c;}
#define BIN_S(op, r) double v##op(vec a, vec b){ return r; }
BIN_V(sub, a.x - b.x, a.y - b.y);
BIN_V(add, a.x + b.x, a.y + b.y);
BIN_S(dot, a.x * b.x + a.y * b.y);
BIN_S(cross, a.x * b.y - a.y * b.x);

/* return a + s * b */
vec vmadd(vec a, double s, vec b)
{
    vec c;
    c.x = a.x + s * b.x;
    c.y = a.y + s * b.y;
    return c;
}

/* check if x0->x1 edge crosses y0->y1 edge. dx = x1 - x0, dy = y1 - y0, then
   solve  x0 + a * dx == y0 + b * dy with a, b in real
   cross both sides with dx, then: (remember, cross product is a scalar)
    x0 X dx = y0 X dx + b * (dy X dx)
   similarly,
    x0 X dy + a * (dx X dy) == y0 X dy
   there is an intersection iff 0 <= a <= 1 and 0 <= b <= 1

   returns: 1 for intersect, -1 for not, 0 for hard to say (if the intersect
   point is too close to y0 or y1)
*/
int intersect(vec x0, vec x1, vec y0, vec y1, double tol, vec *sect)
{
    vec dx = vsub(x1, x0), dy = vsub(y1, y0);
    double d = vcross(dy, dx), a;
    if (!d) return 0; /* edges are parallel */

    a = (vcross(x0, dx) - vcross(y0, dx)) / d;
    if (sect)
        *sect = vmadd(y0, a, dy);

    if (a < -tol || a > 1 + tol) return -1;
    if (a < tol || a > 1 - tol) return 0;

    a = (vcross(x0, dy) - vcross(y0, dy)) / d;
    if (a < 0 || a > 1) return -1;

    return 1;
}

/* distance between x and nearest point on y0->y1 segment.  if the point
   lies outside the segment, returns infinity */
double dist(vec x, vec y0, vec y1, double tol)
{
    vec dy = vsub(y1, y0);
    vec x1, s;
    int r;

    x1.x = x.x + dy.y; x1.y = x.y - dy.x;
    r = intersect(x, x1, y0, y1, tol, &s);
    if (r == -1) return HUGE_VAL;
    s = vsub(s, x);
    return sqrt(vdot(s, s));
}

#define for_v(i, z, p) for(i = 0, z = p->v; i < p->n; i++, z++)
/* returns 1 for inside, -1 for outside, 0 for on edge */
int inside(vec v, polygon p, double tol)
{
    /* should assert p->n > 1 */
    int i, k, crosses, intersectResult;
    vec *pv;
    double min_x, max_x, min_y, max_y;

    for (i = 0; i < p->n; i++) {
        k = (i + 1) % p->n;
        min_x = dist(v, p->v[i], p->v[k], tol);
        if (min_x < tol) return 0;
    }

    min_x = max_x = p->v[0].x;
    min_y = max_y = p->v[1].y;

    /* calculate extent of polygon */
    for_v(i, pv, p) {
        if (pv->x > max_x) max_x = pv->x;
        if (pv->x < min_x) min_x = pv->x;
        if (pv->y > max_y) max_y = pv->y;
        if (pv->y < min_y) min_y = pv->y;
    }
    if (v.x < min_x || v.x > max_x || v.y < min_y || v.y > max_y)
        return -1;

    max_x -= min_x; max_x *= 2;
    max_y -= min_y; max_y *= 2;
    max_x += max_y;

    vec e;
    while (1) {
        crosses = 0;
        /* pick a rand point far enough to be outside polygon */
        e.x = v.x + (1 + rand() / (RAND_MAX + 1.)) * max_x;
        e.y = v.y + (1 + rand() / (RAND_MAX + 1.)) * max_x;

        for (i = 0; i < p->n; i++) {
            k = (i + 1) % p->n;
            intersectResult = intersect(v, e, p->v[i], p->v[k], tol, 0);

            /* picked a bad point, ray got too close to vertex.
               re-pick */
            if (!intersectResult) break;

            if (intersectResult == 1) crosses++;
        }
        if (i == p->n) break;
    }
    return (crosses & 1) ? 1 : -1;
}

// конструктор
point_in_zone_checker::point_in_zone_checker()
{
    zone_real_count = 0;
}

// деструктор
point_in_zone_checker::~point_in_zone_checker()
{
    zone_real_count = 0;
}

// вернуть признаки принадлежности точки зонам
void point_in_zone_checker::ret_b_point_in_zone(int _point_x, int _point_y, bool * _b_res)
{
    vec _point;
    _point.x = _point_x;
    _point.y = _point_y;

    for(int i=0; i<ZONE_MAX; i++)
    {
        _b_res[i] = false;
    }

    for(int i=0; i<zone_real_count; i++)
    {
        vec * vector;
        int vector_size;

        vector_size = Zone[i].countPoint;
        vector = new vec[vector_size];

        for(int j=0; j<vector_size; j++)
        {
            vector[j].x = Zone[i].Point[j].x;
            vector[j].y = Zone[i].Point[j].y;
        }

        polygon_t my_zone;
        my_zone.n = vector_size;
        my_zone.v = vector;

        if(inside(_point, &my_zone, 1e-10) != -1)
        {
            _b_res[i] = true;
        }

        delete[] vector;
    }
}

TZone * point_in_zone_checker::ret_Zone() // вернуть массив зоны
{
    return Zone;
}

int point_in_zone_checker::ret_zone_real_count() // вернуть реальное количество зон
{
    return zone_real_count;
}


void point_in_zone_checker::set_Zone(TZone * _Zone) // установить массив зоны
{
    for(int i=0; i<ZONE_MAX; i++)
    {
        Zone[i].r = _Zone[i].r;
        Zone[i].g = _Zone[i].g;
        Zone[i].b = _Zone[i].b;
        Zone[i].a = _Zone[i].a;
        Zone[i].countPoint = _Zone[i].countPoint;
        for(int j=0; j<10; j++)
        {
            Zone[i].Point[j].x = _Zone[i].Point[j].x;
            Zone[i].Point[j].y = _Zone[i].Point[j].y;
        }
    }

    set_zone_real_count();
}

void point_in_zone_checker::set_zone_real_count() // установить реальное количество зон
{
    zone_real_count = 0;
    for(int i=0; i<ZONE_MAX; i++)
    {
        if(Zone[i].countPoint != 0)
        {
            zone_real_count++;
        }
    }
}
