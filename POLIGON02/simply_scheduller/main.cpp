#include <QApplication>

#include "../input_file_parser/input_file_parser.h"
#include "../point_in_zone_checker/point_in_zone_checker.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // структуры, которые необходимо заполнить --------------------------------------------------------------------------------------------
    TCharSens CharSens[SENS_CHAR_MAX];
    TSensSite SensSite[SENS_MAX];
    TObjectContr ObjectContr[TRACK_MAX];
    TZone Zone[ZONE_MAX];
    // ------------------------------------------------------------------------------------------------------------------------------------

    input_file_parser i_f_p;
    i_f_p.main_func(CharSens,
                    SensSite,
                    ObjectContr,
                    Zone,
                    "../input_files/xml/char_sens/1.xml",
                    "../input_files/xsd/char_sens.xsd",
                    "../input_files/xml/sens_site/1.xml",
                    "../input_files/xsd/sens_site.xsd",
                    "../input_files/xml/object_contr/1.xml",
                    "../input_files/xsd/object_contr.xsd",
                    "../input_files/xml/zone/1.xml",
                    "../input_files/xsd/zone.xsd");

    // печать результатов -----------------------------------------------------------------------------------------------------------------
    qDebug()<<"\n\n";
    qDebug()<<"Печать массива CharSens";
    for(int i=0; i<SENS_CHAR_MAX; i++)
    {
        qDebug()<<QString("CharSens[%1] hMax=%2 hMin=%3 maxCountTrc=%4 rMax=%5 rMin=%6 trustXY=%7 trustH=%8")
                  .arg(i)
                  .arg(CharSens[i].hMax)
                  .arg(CharSens[i].hMin)
                  .arg(CharSens[i].maxCountTrc)
                  .arg(CharSens[i].rMax)
                  .arg(CharSens[i].rMin)
                  .arg(CharSens[i].trustXY)
                  .arg(CharSens[i].trustH);
    }

    qDebug()<<"\n\n";
    qDebug()<<"Печать массива SensSite";
    for(int i=0; i<SENS_MAX; i++)
    {
        qDebug()<<QString("SensSite[%1] sensChar = %2 x=%3 y=%4")
                  .arg(i)
                  .arg(SensSite[i].sensChar)
                  .arg(SensSite[i].x)
                  .arg(SensSite[i].y);
    }

    qDebug()<<"\n\n";
    qDebug()<<"Печать массива ObjectContr";
    for(int i=0; i<TRACK_MAX; i++)
    {
        qDebug()<<QString("ObjectContr[%1] ObjClass=%2 TO=%3 IO=%4 OGP=%5 tStart=%6 tFinish=%7 x=%8 y=%9 h=%10 psi=%11 v=%12 vh=%13 trackBz=%14")
                  .arg(i)
                  .arg(ObjectContr[i].ObjClass)
                  .arg(ObjectContr[i].TO)
                  .arg(ObjectContr[i].IO)
                  .arg(ObjectContr[i].OGP)
                  .arg(ObjectContr[i].tStart)
                  .arg(ObjectContr[i].tFinish)
                  .arg(ObjectContr[i].x)
                  .arg(ObjectContr[i].y)
                  .arg(ObjectContr[i].h)
                  .arg(ObjectContr[i].psi)
                  .arg(ObjectContr[i].v)
                  .arg(ObjectContr[i].vh)
                  .arg(ObjectContr[i].trackBZ);
        for(int j=0; j<ObjectContr[i].countManevr; j++)
        {
            qDebug()<<QString("    Manevr[%1] tStart=%2 tFinish=%3 a=%4 vh=%5 r=%6 ")
                      .arg(j)
                      .arg(ObjectContr[i].Manevr[j].tStart)
                      .arg(ObjectContr[i].Manevr[j].tFinish)
                      .arg(ObjectContr[i].Manevr[j].a)
                      .arg(ObjectContr[i].Manevr[j].vh)
                      .arg(ObjectContr[i].Manevr[j].r);
        }
    }

    qDebug()<<"\n\n";
    qDebug()<<"Печать массива Zone";
    for(int i=0; i<ZONE_MAX; i++)
    {
        qDebug()<<QString("Zone[%1] r=%2 g=%3 b=%4 a=%5 countPoint=%6")
                  .arg(i)
                  .arg(Zone[i].r)
                  .arg(Zone[i].g)
                  .arg(Zone[i].b)
                  .arg(Zone[i].a)
                  .arg(Zone[i].countPoint);
        for(int j=0; j<Zone[i].countPoint; j++)
        {
            qDebug()<<QString("    point[%1] x=%2 y=%3")
                      .arg(j)
                      .arg(Zone[i].Point[j].x)
                      .arg(Zone[i].Point[j].y);
        }
    }
    // ------------------------------------------------------------------------------------------------------------------------------------

    bool b_res[ZONE_MAX];
    point_in_zone_checker p_i_z_c;
    p_i_z_c.set_Zone(Zone);
    p_i_z_c.ret_b_point_in_zone(200000, 100000, b_res);
//    p_i_z_c.ret_b_point_in_zone(10, 50, b_res);

    QString str_res;
    str_res = "";
    for(int i=0; i<ZONE_MAX; i++)
    {
        str_res = str_res + QString("%1").arg(b_res[i]);
    }
    qDebug()<<"\n\n";
    qDebug()<<str_res;

    return 0;
}
