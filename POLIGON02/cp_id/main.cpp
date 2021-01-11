#include <stddef.h>
#include <QApplication>
#include <QTextCodec>
#include <QFile>
#include <QXmlStreamReader>
#include <QTextStream>

//#include "char_sens_form.h"
//#include "sens_site_form.h"
//#include "standard_form.h"
//#include "test_widget.h"
//#include "standard_maneuver_scroll_area.h"

#include "char_sens_form.h"
#include "sens_site_form.h"
#include "etalon_form.h"
#include "maneuver_form.h"
#include "zone_form.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec * c_o_d_e_c = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(c_o_d_e_c);
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    QTextCodec::setCodecForCStrings(c_o_d_e_c);
    QTextCodec::setCodecForTr(c_o_d_e_c);
#endif

    /*
    // имя каталога с xsd- и xsl-файлами
    QString char_sens_xsd_xsl_dir_name;
    QString sens_site_xsd_xsl_dir_name;
    QString air_xsd_xsl_dir_name;

    // имя каталога с вариантами контрольной задачи
    QString char_sens_variant_dir_name;
    QString sens_site_variant_dir_name;
    QString air_variant_dir_name;

    // полное имя каталога приложения
    QString app_full_dir_path;

    // полное имя каталога на один уровень выше каталога приложения
    QString app_up_full_dir_path;
    QRegExp re("[a-zA-z0-9_-]*@");
    */

    // имя xml-, xsd- и xsl-файла
    QString char_sens_variant_file_name;
    QString char_sens_xsd_xsl_file_name;
    QString sens_site_variant_file_name;
    QString sens_site_xsd_xsl_file_name;
    QString etalon_variant_file_name;
    QString etalon_xsd_xsl_file_name;
    QString zone_variant_file_name;
    QString zone_xsd_xsl_file_name;

    // полное имя каталога с xsd- и xsl-файлами
    QString char_sens_xsd_full_dir_path;
    QString sens_site_xsd_full_dir_path;
    QString etalon_xsd_full_dir_path;
    QString zone_xsd_full_dir_path;

    // полное имя каталога с xsd- и xsl-файлами
    QString char_sens_xsl_full_dir_path;
    QString sens_site_xsl_full_dir_path;
    QString etalon_xsl_full_dir_path;
    QString zone_xsl_full_dir_path;

    // полное имя каталога с html-файлами
    QString char_sens_html_full_dir_path;
    QString sens_site_html_full_dir_path;
    QString etalon_html_full_dir_path;
    QString zone_html_full_dir_path;

    // полное имя каталога с вариантами контрольной задачи
    QString char_sens_variant_full_dir_path;
    QString sens_site_variant_full_dir_path;
    QString etalon_variant_full_dir_path;
    QString zone_variant_full_dir_path;

    /*
    // старый способ задания исходных данных по расположению файлов
    char_sens_xsd_xsl_dir_name = "char_sens_xsd_xsl";
    sens_site_xsd_xsl_dir_name = "sens_site_xsd_xsl";
    air_xsd_xsl_dir_name = "air_xsd_xsl";
    char_sens_variant_dir_name = "char_sens_variant";
    sens_site_variant_dir_name = "sens_site_variant";
    air_variant_dir_name = "air_variant";
    char_sens_variant_file_name = "1";
    sens_site_variant_file_name = "1";
    air_variant_file_name = "1";
    char_sens_xsd_xsl_file_name = "CharSens";
    sens_site_xsd_xsl_file_name = "SensSite";
    air_xsd_xsl_file_name = "air";
    app_full_dir_path = QApplication::applicationDirPath();
    app_up_full_dir_path = app_full_dir_path;
    app_up_full_dir_path.append("@");
    app_up_full_dir_path.replace(re,"");
    char_sens_xsd_xsl_full_dir_path = app_up_full_dir_path + char_sens_xsd_xsl_dir_name;
    sens_site_xsd_xsl_full_dir_path = app_up_full_dir_path + sens_site_xsd_xsl_dir_name;
    air_xsd_xsl_full_dir_path = app_up_full_dir_path + air_xsd_xsl_dir_name;
    char_sens_variant_full_dir_path = app_up_full_dir_path + char_sens_variant_dir_name;
    sens_site_variant_full_dir_path = app_up_full_dir_path + sens_site_variant_dir_name;
    air_variant_full_dir_path = app_up_full_dir_path + air_variant_dir_name;
    */

    QXmlStreamReader * xml_reader;
    xml_reader = new QXmlStreamReader();

    QFile xml_file("../cp_id/init.xml");
    if (!xml_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        delete xml_reader;
        xml_reader = NULL;
        return -1;
    }
    else
    {
        QString xml_file_data;

        xml_file_data = xml_file.readAll();
        xml_reader->addData(xml_file_data);

        while(!xml_reader->atEnd())
        {
            if(xml_reader->isStartElement()) // если xml_reader наткнулся на открывающийся элемент
            {
                QString element_name;
                QXmlStreamAttributes attributes;

                attributes = xml_reader->attributes();
                element_name = xml_reader->name().toString();

                if(element_name == "init")
                {
                }
                // ----------------------------------------------------------------------------------------------------
                else if(element_name == "char_sens_variant_full_dir_path")
                {
                    char_sens_variant_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "char_sens_xsd_full_dir_path")
                {
                    char_sens_xsd_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "char_sens_xsl_full_dir_path")
                {
                    char_sens_xsl_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "char_sens_html_full_dir_path")
                {
                    char_sens_html_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "char_sens_variant_file_name")
                {
                    char_sens_variant_file_name = xml_reader->readElementText();
                }
                else if(element_name == "char_sens_xsd_xsl_file_name")
                {
                    char_sens_xsd_xsl_file_name = xml_reader->readElementText();
                }
                // ----------------------------------------------------------------------------------------------------
                else if(element_name == "sens_site_variant_full_dir_path")
                {
                    sens_site_variant_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "sens_site_xsd_full_dir_path")
                {
                    sens_site_xsd_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "sens_site_xsl_full_dir_path")
                {
                    sens_site_xsl_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "sens_site_html_full_dir_path")
                {
                    sens_site_html_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "sens_site_variant_file_name")
                {
                    sens_site_variant_file_name = xml_reader->readElementText();
                }
                else if(element_name == "sens_site_xsd_xsl_file_name")
                {
                    sens_site_xsd_xsl_file_name = xml_reader->readElementText();
                }
                // ----------------------------------------------------------------------------------------------------
                else if(element_name == "etalon_variant_full_dir_path")
                {
                    etalon_variant_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "etalon_xsd_full_dir_path")
                {
                    etalon_xsd_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "etalon_xsl_full_dir_path")
                {
                    etalon_xsl_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "etalon_html_full_dir_path")
                {
                    etalon_html_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "etalon_variant_file_name")
                {
                    etalon_variant_file_name = xml_reader->readElementText();
                }
                else if(element_name == "etalon_xsd_xsl_file_name")
                {
                    etalon_xsd_xsl_file_name = xml_reader->readElementText();
                }
                else if(element_name == "zone_variant_full_dir_path")
                {
                    zone_variant_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "zone_xsd_full_dir_path")
                {
                    zone_xsd_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "zone_xsl_full_dir_path")
                {
                    zone_xsl_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "zone_html_full_dir_path")
                {
                    zone_html_full_dir_path = xml_reader->readElementText();
                }
                else if(element_name == "zone_variant_file_name")
                {
                    zone_variant_file_name = xml_reader->readElementText();
                }
                else if(element_name == "zone_xsd_xsl_file_name")
                {
                    zone_xsd_xsl_file_name = xml_reader->readElementText();
                }
                else
                {
                    return -2;
                }
            }
            xml_reader->readNext();
        }
    }
    delete xml_reader;
    xml_reader = NULL;

//    char_sens_form * ptr_char_sens_form;
//    ptr_char_sens_form = new char_sens_form(char_sens_variant_full_dir_path, char_sens_variant_file_name,
//                                            char_sens_xsd_xsl_full_dir_path, char_sens_xsd_xsl_file_name,
//                                            char_sens_xsd_xsl_full_dir_path, char_sens_xsd_xsl_file_name);

//    sens_site_form * ptr_sens_site_form;
//    ptr_sens_site_form = new sens_site_form(sens_site_variant_full_dir_path, sens_site_variant_file_name,
//                                            sens_site_xsd_xsl_full_dir_path, sens_site_xsd_xsl_file_name,
//                                            sens_site_xsd_xsl_full_dir_path, sens_site_xsd_xsl_file_name);

//    standard_form * ptr_standard_form;
//    ptr_standard_form = new standard_form(standard_variant_full_dir_path, standard_variant_file_name,
//                                          standard_xsd_xsl_full_dir_path, standard_xsd_xsl_file_name,
//                                          standard_xsd_xsl_full_dir_path, standard_xsd_xsl_file_name);


    char_sens_form * ptr_char_sens_form;
    ptr_char_sens_form = new char_sens_form(char_sens_variant_full_dir_path, char_sens_variant_file_name,
                                            char_sens_xsd_full_dir_path, char_sens_xsd_xsl_file_name,
                                            char_sens_xsl_full_dir_path, char_sens_xsd_xsl_file_name,
                                            char_sens_html_full_dir_path);

    sens_site_form * ptr_sens_site_form;
    ptr_sens_site_form = new sens_site_form(sens_site_variant_full_dir_path, sens_site_variant_file_name,
                                            sens_site_xsd_full_dir_path, sens_site_xsd_xsl_file_name,
                                            sens_site_xsl_full_dir_path, sens_site_xsd_xsl_file_name,
                                            sens_site_html_full_dir_path);

    maneuver_form * ptr_maneuver_form;
    ptr_maneuver_form = new maneuver_form();

    etalon_form * ptr_etalon_form;
    ptr_etalon_form = new etalon_form(etalon_variant_full_dir_path, etalon_variant_file_name,
                                      etalon_xsd_full_dir_path, etalon_xsd_xsl_file_name,
                                      etalon_xsl_full_dir_path, etalon_xsd_xsl_file_name,
                                      etalon_html_full_dir_path,
                                      ptr_maneuver_form->ret_table_lo());

    zone_form * ptr_zone_form;
    ptr_zone_form = new zone_form(zone_variant_full_dir_path, zone_variant_file_name,
                                  zone_xsd_full_dir_path, zone_xsd_xsl_file_name,
                                  zone_xsl_full_dir_path, zone_xsd_xsl_file_name,
                                  zone_html_full_dir_path);



//    standard_maneuver_scroll_area * ptr_standard_maneuver_s_a;
//    ptr_standard_maneuver_s_a = new standard_maneuver_scroll_area();

    QTabWidget t_w;
    t_w.addTab(ptr_char_sens_form, "Типы источников");
    t_w.addTab(ptr_sens_site_form, "Расположение источников");
    t_w.addTab(ptr_zone_form, "Зоны");
    t_w.addTab(ptr_etalon_form, "Эталоны");
    t_w.addTab(ptr_maneuver_form, "Маневры эталонов");
    t_w.showMaximized();

//    main_widget ptr_main_widget;
//    ptr_main_widget.addTab(ptr_char_sens_form,"Типы источников");
//    ptr_main_widget.addTab(ptr_sens_site_form,"Расположение источников");
//    ptr_main_widget.addTab(ptr_standard_form,"Эталоны");
//    ptr_main_widget.addTab(ptr_standard_maneuver_s_a,"Маневры");

//    ptr_main_widget.addTab(ptr_example_form, "Тестовая форма");

//    ptr_main_widget.showMaximized();

//    test_widget * t_w;
//    t_w = new test_widget();

    a.exec();

    delete ptr_char_sens_form;
    delete ptr_sens_site_form;
    delete ptr_etalon_form;
    delete ptr_maneuver_form;

    return 0;
}
