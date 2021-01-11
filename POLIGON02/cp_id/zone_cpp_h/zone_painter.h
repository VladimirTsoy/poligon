#ifndef ZONE_PAINTER_H
#define ZONE_PAINTER_H

#include <QWidget>
#include <QFile>
#include <QImageReader>
#include <QPainter>
#include <QPen>
#include <QString>
#include <QDebug>

#include "zone_row_view.h"

class zone_painter : public QWidget
{
    Q_OBJECT
public:
    zone_painter();
    ~zone_painter();

    // установка параметров
    void set_par(zone_row_view * _first,
                 zone_row_view * _last);

    // преобразование координат (отображение)
    QPointF coord_translate(float _x, float _y);

    // пересчет координат (из одной системы в другую)
    QPointF coord_conversion(float _x, float _y);

    // рисование зоны
    void draw_zone(zone_row_view * iter_zone);

    // событие отображения
    void paintEvent(QPaintEvent *);

private:
    QPainter * painter;

    QString full_file_name_map; // полное имя пути к файлу с картой
    int map_width;              // ширина карты
    int map_height;             // высота карты

    int delta_x;                // смещение центра координат по оси x
    int delta_y;                // смещение центра координат по оси y
    float scale_x;              // масштаб
    float scale_y;              // масштаб

    zone_row_view * first;             // указатель на первый элемент
    zone_row_view * last;              // указатель на последний элемент
};

#endif // ZONE_PAINTER_H
