#include "zone_painter.h"

zone_painter::zone_painter()
{
    full_file_name_map = "../input_files/map/map.jpg";
    map_width = 1235;
    map_height = 1078;
//    delta_x = 536;
//    delta_y = 671;
    delta_x = 528;
    delta_y = 1028;
//    scale = 1;
    scale_x = 0.0015;
    scale_y = 0.0015;
}

zone_painter::~zone_painter()
{

}

// установка параметров
void zone_painter::set_par(zone_row_view * _first,
                           zone_row_view * _last)
{
    first = _first;
    last = _last;
}

// преобразование координат (отображение)
QPointF zone_painter::coord_translate(float _x, float _y)
{
    return QPointF(_x-(float)map_width/2.0, _y-(float)map_height/2.0);
}

// пересчет координат (из одной системы в другую)
QPointF zone_painter::coord_conversion(float _x, float _y)
{
    return coord_translate(scale_x*_x+0.0, -scale_y*_y+0.0);
}

// рисование зоны
void zone_painter::draw_zone(zone_row_view * iter_zone)
{
    QPolygon pol;

    zone_point_row_view * iter_zone_point;

    iter_zone_point = iter_zone->ret_first();

    while(iter_zone_point != NULL)
    {
        pol<<coord_conversion(iter_zone_point->ret_y()->ret_value().toInt(),
                              iter_zone_point->ret_x()->ret_value().toInt()).toPoint();
        iter_zone_point = iter_zone_point->ret_next();
    }

    painter->drawPolygon(pol);
}

// событие отображения
void zone_painter::paintEvent(QPaintEvent *)
{
    painter = new QPainter();

    painter->begin(this);

    painter->translate(painter->device()->width()/2.0, painter->device()->height()/2.0);

    QPixmap pixmap(full_file_name_map);
    painter->drawPixmap(-0.5*(float)map_width,
                        -0.5*(float)map_height,
                        map_width,
                        map_height,
                        pixmap);

    painter->translate(delta_x,delta_y);

    zone_row_view * iter_zone;
    iter_zone = first;
    while(iter_zone != NULL)
     {
        // установка параметров пера
        QPen pen;
        pen.setColor(QColor::fromRgb(0, 0, 0));
        pen.setWidth(1);

        painter->setPen(pen);
        painter->setBrush(QBrush(QColor::fromRgbF(iter_zone->ret_r()->ret_value().toInt()/255.0,
                                                  iter_zone->ret_g()->ret_value().toInt()/255.0,
                                                  iter_zone->ret_b()->ret_value().toInt()/255.0,
                                                  iter_zone->ret_a()->ret_value().toInt()/255.0)));
        draw_zone(iter_zone);
        iter_zone = iter_zone->ret_next();
    }

    painter->end();

    delete painter;
    painter = NULL;
}
