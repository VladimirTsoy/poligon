#ifndef ZONE_CONVERTOR_H
#define ZONE_CONVERTOR_H

#include <QStringList>
#include <math.h>
#include <QDebug>

class zone_convertor
{
public:
    zone_convertor();
    ~zone_convertor();

    QString number_data_view(QString _data);
    QString number_view_data(QString _view);

    QString r_data_view(QString _data);
    QString r_view_data(QString _view);

    QString g_data_view(QString _data);
    QString g_view_data(QString _view);

    QString b_data_view(QString _data);
    QString b_view_data(QString _view);

    QString a_data_view(QString _data);
    QString a_view_data(QString _view);

    QString point_number_data_view(QString _data);
    QString point_number_view_data(QString _view);

    QString point_x_data_view(QString _data);
    QString point_x_view_data(QString _view);

    QString point_y_data_view(QString _data);
    QString point_y_view_data(QString _view);
};

#endif // ZONE_CONVERTOR_H
