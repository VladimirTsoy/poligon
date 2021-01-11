#ifndef SENS_SITE_CONVERTOR_H
#define SENS_SITE_CONVERTOR_H

#include <QStringList>
#include <math.h>

// конвертор
class sens_site_convertor
{
public:
    sens_site_convertor();
    ~sens_site_convertor();

    QString number_data_view(QString _data);
    QString number_view_data(QString _view);

    QString charSens_data_view(QString _data);
    QString charSens_view_data(QString _view);

    QString x_data_view(QString _data);
    QString x_view_data(QString _view);

    QString y_data_view(QString _data);
    QString y_view_data(QString _view);
};

#endif // SENS_SITE_CONVERTOR_H
