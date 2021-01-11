#ifndef CHAR_SENS_CONVERTOR_H
#define CHAR_SENS_CONVERTOR_H

#include <QStringList>
#include <math.h>

// конвертор
class char_sens_convertor
{
public:
    char_sens_convertor();
    ~char_sens_convertor();

    QString number_data_view(QString _data);
    QString number_view_data(QString _view);

    QString hMax_data_view(QString _data);
    QString hMax_view_data(QString _view);

    QString hMin_data_view(QString _data);
    QString hMin_view_data(QString _view);

    QString maxCountTrc_data_view(QString _data);
    QString maxCountTrc_view_data(QString _view);

    QString rMax_data_view(QString _data);
    QString rMax_view_data(QString _view);

    QString rMin_data_view(QString _data);
    QString rMin_view_data(QString _view);

    QString trustXY_data_view(QString _data);
    QString trustXY_view_data(QString _view);

    QString trustH_data_view(QString _data);
    QString trustH_view_data(QString _view);
};

#endif // CHAR_SENS_CONVERTOR_H
