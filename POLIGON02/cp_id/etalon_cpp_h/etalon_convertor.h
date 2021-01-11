#ifndef ETALON_CONVERTOR_H
#define ETALON_CONVERTOR_H

#include <QStringList>
#include <math.h>
#include <QDebug>

// конвертор
class etalon_convertor
{
public:
    etalon_convertor();
    ~etalon_convertor();

    QStringList etalon_s_l_empty;

    QString number_data_view(QString _data);
    QString number_view_data(QString _view);

    QString ObjClass_data_view(QString _data);
    QString ObjClass_view_data(QString _view);

    QString TO_data_view(QString _major_data, QString _data);
    QString TO_view_data(QString _major_view, QString _view);

    QString IO_data_view(QString _data);
    QString IO_view_data(QString _view);

    QString OGP_data_view(QString _data);
    QString OGP_view_data(QString _view);

    QString tStart_data_view(QString _data);
    QString tStart_view_data(QString _view);

    QString tFinish_data_view(QString _data);
    QString tFinish_view_data(QString _view);

    QString x_data_view(QString _data);
    QString x_view_data(QString _view);

    QString y_data_view(QString _data);
    QString y_view_data(QString _view);

    QString h_data_view(QString _data);
    QString h_view_data(QString _view);

    QString psi_data_view(QString _data, int _decimals);
    QString psi_view_data(QString _view);

    QString v_data_view(QString _data);
    QString v_view_data(QString _view);

    QString vh_data_view(QString _data);
    QString vh_view_data(QString _view);

    QString maneuver_number_data_view(QString _data);
    QString maneuver_number_view_data(QString _view);

    QString maneuver_tStart_data_view(QString _data);
    QString maneuver_tStart_view_data(QString _view);

    QString maneuver_tFinish_data_view(QString _data);
    QString maneuver_tFinish_view_data(QString _view);

    QString maneuver_a_data_view(QString _data);
    QString maneuver_a_view_data(QString _view);

    QString maneuver_vh_data_view(QString _data);
    QString maneuver_vh_view_data(QString _view);

    QString maneuver_r_data_view(QString _data);
    QString maneuver_r_view_data(QString _view);

    QStringList etalon_s_l_ObjClass_data;
    QStringList etalon_s_l_ObjClass_view;

    QStringList etalon_s_l_TO_Air_data;
    QStringList etalon_s_l_TO_Air_view;

    QStringList etalon_s_l_TO_Sea_data;
    QStringList etalon_s_l_TO_Sea_view;

    QStringList etalon_s_l_TO_Ground_data;
    QStringList etalon_s_l_TO_Ground_view;

    QStringList etalon_s_l_TO_Surface_data;
    QStringList etalon_s_l_TO_Surface_view;

    QStringList etalon_s_l_IO_data;
    QStringList etalon_s_l_IO_view;

    QStringList etalon_s_l_OGP_data;
    QStringList etalon_s_l_OGP_view;
};

QStringList ret_etalon_s_l_empty();

QStringList ret_etalon_s_l_ObjClass_data();
QStringList ret_etalon_s_l_ObjClass_view();

QStringList ret_etalon_s_l_TO_Air_data();
QStringList ret_etalon_s_l_TO_Air_view();

QStringList ret_etalon_s_l_TO_Sea_data();
QStringList ret_etalon_s_l_TO_Sea_view();

QStringList ret_etalon_s_l_TO_Ground_data();
QStringList ret_etalon_s_l_TO_Ground_view();

QStringList ret_etalon_s_l_TO_Surface_data();
QStringList ret_etalon_s_l_TO_Surface_view();

QStringList ret_etalon_s_l_IO_data();
QStringList ret_etalon_s_l_IO_view();

QStringList ret_etalon_s_l_OGP_data();
QStringList ret_etalon_s_l_OGP_view();

#endif // ETALON_CONVERTOR_H
