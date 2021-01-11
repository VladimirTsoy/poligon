#include "etalon_convertor.h"

etalon_convertor::etalon_convertor()
{
    etalon_s_l_empty = ret_etalon_s_l_empty();

    etalon_s_l_ObjClass_data = ret_etalon_s_l_ObjClass_data();
    etalon_s_l_ObjClass_view = ret_etalon_s_l_ObjClass_view();

    etalon_s_l_TO_Air_data = ret_etalon_s_l_TO_Air_data();
    etalon_s_l_TO_Air_view = ret_etalon_s_l_TO_Air_view();

    etalon_s_l_TO_Sea_data = ret_etalon_s_l_TO_Sea_data();
    etalon_s_l_TO_Sea_view = ret_etalon_s_l_TO_Sea_view();

    etalon_s_l_TO_Ground_data = ret_etalon_s_l_TO_Ground_data();
    etalon_s_l_TO_Ground_view = ret_etalon_s_l_TO_Ground_view();

    etalon_s_l_TO_Surface_data = ret_etalon_s_l_TO_Surface_data();
    etalon_s_l_TO_Surface_view = ret_etalon_s_l_TO_Surface_view();

    etalon_s_l_IO_data = ret_etalon_s_l_IO_data();
    etalon_s_l_IO_view = ret_etalon_s_l_IO_view();

    etalon_s_l_OGP_data = ret_etalon_s_l_OGP_data();
    etalon_s_l_OGP_view = ret_etalon_s_l_OGP_view();
}

etalon_convertor::~etalon_convertor()
{

}

QString etalon_convertor::number_data_view(QString _data)
{
    return _data;
}

QString etalon_convertor::number_view_data(QString _view)
{
    return _view;
}

QString etalon_convertor::ObjClass_data_view(QString _data)
{
    int pos;
    pos = -1;

    for(int i=0; i<etalon_s_l_ObjClass_data.size(); i++)
    {
        if(_data == etalon_s_l_ObjClass_data[i])
        {
            pos = i;
            break;
        }
    }

    if(pos == -1)
    {
        return "";
    }
    else
    {
        return etalon_s_l_ObjClass_view[pos];
    }
}

QString etalon_convertor::ObjClass_view_data(QString _view)
{
    int pos;
    pos = -1;

    for(int i=0; i<etalon_s_l_ObjClass_view.size(); i++)
    {
        if(_view == etalon_s_l_ObjClass_view[i])
        {
            pos = i;
            break;
        }
    }

    if(pos == -1)
    {
        return "";
    }
    else
    {
        return etalon_s_l_ObjClass_data[pos];
    }
}

QString etalon_convertor::TO_data_view(QString _major_data, QString _data)
{
    QStringList minor_s_l_data;
    QStringList minor_s_l_view;

    if(_major_data == "1")
    {
        minor_s_l_data = etalon_s_l_TO_Air_data;
        minor_s_l_view = etalon_s_l_TO_Air_view;
    }
    else if(_major_data == "2")
    {
        minor_s_l_data = etalon_s_l_TO_Sea_data;
        minor_s_l_view = etalon_s_l_TO_Sea_view;
    }
    else if(_major_data == "3")
    {
        minor_s_l_data = etalon_s_l_TO_Ground_data;
        minor_s_l_view = etalon_s_l_TO_Ground_view;
    }
    else if(_major_data == "4")
    {
        minor_s_l_data = etalon_s_l_TO_Surface_data;
        minor_s_l_view = etalon_s_l_TO_Surface_view;
    }
    else
    {
        return "";
    }

    int pos;
    pos = -1;

    for(int i=0; i<minor_s_l_data.size(); i++)
    {
        if(_data == minor_s_l_data[i])
        {
            pos = i;
            break;
        }
    }

    if(pos == -1)
    {
        return "";
    }
    else
    {
        return minor_s_l_view[pos];
    }
}

QString etalon_convertor::TO_view_data(QString _major_view, QString _view)
{
    QStringList minor_s_l_data;
    QStringList minor_s_l_view;

    if(_major_view == "Воздушный")
    {
        minor_s_l_data = etalon_s_l_TO_Air_data;
        minor_s_l_view = etalon_s_l_TO_Air_view;
    }
    else if(_major_view == "Надводный")
    {
        minor_s_l_data = etalon_s_l_TO_Sea_data;
        minor_s_l_view = etalon_s_l_TO_Sea_view;
    }
    else if(_major_view == "Наземный")
    {
        minor_s_l_data = etalon_s_l_TO_Ground_data;
        minor_s_l_view = etalon_s_l_TO_Ground_view;
    }
    else if(_major_view == "Неопределенный")
    {
        minor_s_l_data = etalon_s_l_TO_Surface_data;
        minor_s_l_view = etalon_s_l_TO_Surface_view;
    }
    else
    {
        return "";
    }

    int pos;
    pos = -1;

    for(int i=0; i<minor_s_l_view.size(); i++)
    {
        if(_view == minor_s_l_view[i])
        {
            pos = i;
            break;
        }
    }

    if(pos == -1)
    {
        return "";
    }
    else
    {
        return minor_s_l_data[pos];
    }
}

QString etalon_convertor::IO_data_view(QString _data)
{
    int pos;
    pos = -1;

    for(int i=0; i<etalon_s_l_IO_data.size(); i++)
    {
        if(_data == etalon_s_l_IO_data[i])
        {
            pos = i;
            break;
        }
    }

    if(pos == -1)
    {
        return "";
    }
    else
    {
        return etalon_s_l_IO_view[pos];
    }
}

QString etalon_convertor::IO_view_data(QString _view)
{
    int pos;
    pos = -1;

    for(int i=0; i<etalon_s_l_IO_view.size(); i++)
    {
        if(_view == etalon_s_l_IO_view[i])
        {
            pos = i;
            break;
        }
    }

    if(pos == -1)
    {
        return "";
    }
    else
    {
        return etalon_s_l_IO_data[pos];
    }
}

QString etalon_convertor::OGP_data_view(QString _data)
{
    int pos;
    pos = -1;

    for(int i=0; i<etalon_s_l_OGP_data.size(); i++)
    {
        if(_data == etalon_s_l_OGP_data[i])
        {
            pos = i;
            break;
        }
    }

    if(pos == -1)
    {
        return "";
    }
    else
    {
        return etalon_s_l_OGP_view[pos];
    }
}

QString etalon_convertor::OGP_view_data(QString _view)
{
    int pos;
    pos = -1;

    for(int i=0; i<etalon_s_l_OGP_view.size(); i++)
    {
        if(_view == etalon_s_l_OGP_view[i])
        {
            pos = i;
            break;
        }
    }

    if(pos == -1)
    {
        return "";
    }
    else
    {
        return etalon_s_l_OGP_data[pos];
    }
}

QString etalon_convertor::tStart_data_view(QString _data)
{
    return _data;
}

QString etalon_convertor::tStart_view_data(QString _view)
{
    return _view;
}

QString etalon_convertor::tFinish_data_view(QString _data)
{
    return _data;
}

QString etalon_convertor::tFinish_view_data(QString _view)
{
    return _view;
}

QString etalon_convertor::x_data_view(QString _data)
{
    return _data;
}

QString etalon_convertor::x_view_data(QString _view)
{
    return _view;
}

QString etalon_convertor::y_data_view(QString _data)
{
    return _data;
}

QString etalon_convertor::y_view_data(QString _view)
{
    return _view;
}

QString etalon_convertor::h_data_view(QString _data)
{
    return _data;
}

QString etalon_convertor::h_view_data(QString _view)
{
    return _view;
}

QString etalon_convertor::psi_data_view(QString _data, int _decimals)
{
    if(_data == "")
    {
        return "";
    }
    QString _view;
    double _val;
    _val = _data.toDouble() * 180.0 / M_PI;
    _view = QString("%1").arg(_val, 0, 'f', _decimals);
    return _view;
}

QString etalon_convertor::psi_view_data(QString _view)
{
    if(_view == "")
    {
        return "";
    }
    QString _data;
    _data = QString("%1").arg(_view.toDouble() * M_PI / 180.0);
    return _data;
}

QString etalon_convertor::v_data_view(QString _data)
{
    return _data;
}

QString etalon_convertor::v_view_data(QString _view)
{
    return _view;
}

QString etalon_convertor::vh_data_view(QString _data)
{
    return _data;
}

QString etalon_convertor::vh_view_data(QString _view)
{
    return _view;
}

QString etalon_convertor::maneuver_number_data_view(QString _data)
{
    return _data;
}

QString etalon_convertor::maneuver_number_view_data(QString _view)
{
    return _view;
}

QString etalon_convertor::maneuver_tStart_data_view(QString _data)
{
    return _data;
}

QString etalon_convertor::maneuver_tStart_view_data(QString _view)
{
    return _view;
}

QString etalon_convertor::maneuver_tFinish_data_view(QString _data)
{
    return _data;
}

QString etalon_convertor::maneuver_tFinish_view_data(QString _view)
{
    return _view;
}

QString etalon_convertor::maneuver_a_data_view(QString _data)
{
    return _data;
}

QString etalon_convertor::maneuver_a_view_data(QString _view)
{
    return _view;
}

QString etalon_convertor::maneuver_vh_data_view(QString _data)
{
    return _data;
}

QString etalon_convertor::maneuver_vh_view_data(QString _view)
{
    return _view;
}

QString etalon_convertor::maneuver_r_data_view(QString _data)
{
    return _data;
}

QString etalon_convertor::maneuver_r_view_data(QString _view)
{
    return _view;
}

QStringList ret_etalon_s_l_empty()
{
    QStringList etalon_s_l_empty;
    etalon_s_l_empty.clear();
    return etalon_s_l_empty;
}

QStringList ret_etalon_s_l_ObjClass_data()
{
    QStringList etalon_s_l_ObjClass_data;
    etalon_s_l_ObjClass_data << "1"         << "2"         << "3"        << "4";
    return etalon_s_l_ObjClass_data;
}

QStringList ret_etalon_s_l_ObjClass_view()
{
    QStringList etalon_s_l_ObjClass_view;
    etalon_s_l_ObjClass_view << "Воздушный" << "Надводный" << "Наземный" << "Неопределенный";
    return etalon_s_l_ObjClass_view;
}

QStringList ret_etalon_s_l_TO_Air_data()
{
    QStringList etalon_s_l_TO_Air_data;
    etalon_s_l_TO_Air_data << "0"          << "1"      <<"2"        << "8"    << "10" << "11" << "14" << "15" << "17" << "35"  << "36"  << "51" << "53";
    return etalon_s_l_TO_Air_data;
}

QStringList ret_etalon_s_l_TO_Air_view()
{
    QStringList etalon_s_l_TO_Air_view;
    etalon_s_l_TO_Air_view << "Не опознан" << "Ракета" << "Самолет" << "ГЗЛА" << "БР" << "КР" << "СА" << "ТА" << "БП" << "СКР" << "ТКР" << "СР" << "ДРЛОУ";
    return etalon_s_l_TO_Air_view;
}

QStringList ret_etalon_s_l_TO_Sea_data()
{
    QStringList etalon_s_l_TO_Sea_data;
    etalon_s_l_TO_Sea_data << "0"          << "10"      << "11"      << "12";
    return etalon_s_l_TO_Sea_data;
}

QStringList ret_etalon_s_l_TO_Sea_view()
{
    QStringList etalon_s_l_TO_Sea_view;
    etalon_s_l_TO_Sea_view << "Не опознан" << "Крейсер" << "Эсминец" << "Фрегат";
    return etalon_s_l_TO_Sea_view;
}

QStringList ret_etalon_s_l_TO_Ground_data()
{
    QStringList etalon_s_l_TO_Ground_data;
    etalon_s_l_TO_Ground_data << "0"          << "1"               << "2"        << "3";
    return etalon_s_l_TO_Ground_data;
}

QStringList ret_etalon_s_l_TO_Ground_view()
{
    QStringList etalon_s_l_TO_Ground_view;
    etalon_s_l_TO_Ground_view << "Не опознан" << "Командный пункт" << "Аэродром" << "Танк";
    return etalon_s_l_TO_Ground_view;
}

QStringList ret_etalon_s_l_TO_Surface_data()
{
    QStringList etalon_s_l_TO_Surface_data;
    etalon_s_l_TO_Surface_data << "0";
    return etalon_s_l_TO_Surface_data;
}

QStringList ret_etalon_s_l_TO_Surface_view()
{
    QStringList etalon_s_l_TO_Surface_view;
    etalon_s_l_TO_Surface_view << "Не определен";
    return etalon_s_l_TO_Surface_view;
}

QStringList ret_etalon_s_l_IO_data()
{
    QStringList etalon_s_l_IO_data;
    etalon_s_l_IO_data << "0"          << "3"                   << "6";
    return etalon_s_l_IO_data;
}

QStringList ret_etalon_s_l_IO_view()
{
    QStringList etalon_s_l_IO_view;
    etalon_s_l_IO_view << "Не опознан" << "Воздушный противник" << "Свой выполняющий боевую задачу";
    return etalon_s_l_IO_view;
}

QStringList ret_etalon_s_l_OGP_data()
{
    QStringList etalon_s_l_OGP_data;
    etalon_s_l_OGP_data << "0"          << "1"     << "2"                       << "3";
    return etalon_s_l_OGP_data;
}

QStringList ret_etalon_s_l_OGP_view()
{
    QStringList etalon_s_l_OGP_data;
    etalon_s_l_OGP_data << "Не опознан" << "Чужой" << "Свой, общее опознавание" << "Свой, гарантированное опознавание";
    return etalon_s_l_OGP_data;
}
