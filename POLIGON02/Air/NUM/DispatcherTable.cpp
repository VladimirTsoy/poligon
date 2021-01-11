#include <QList>
#include <QtXml>

#include "DispatcherTable.h"

namespace N_U_M
{

DispatcherTable::DispatcherTable(){}

TableIvo* DispatcherTable::ReadIvo(const char* fileIvo)             //Чтение xml-файла с таблицей ИВО
{
    qDebug()<<fileIvo;
    QDomDocument doc;
    QFile file(fileIvo);
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return NULL;

    qDebug()<<"badger";

    QDomNodeList ivoI = doc.elementsByTagName("ivoI");

    //читая файл, вычисляем максимальный эл-т массива
    int max_el = -1;
    int cur_val;
    for (int i = 0; i < ivoI.size(); i++)
    {
        cur_val = ivoI.at(i).toElement().attribute("ivo").toInt();
        if (cur_val > max_el)
        {
            max_el = cur_val;
        }
    }


    TableIvo* tableIvo = new TableIvo;
    tableIvo->count = max_el+1;


    //выделяем место под массив
    tableIvo->array = new QList<int>*[tableIvo->count];
    for(int i=0;i<tableIvo->count;i++)
    {
        tableIvo->array[i] = new QList<int>[tableIvo->count];
    }

    //читая файл, заполняем массив
    for (int i = 0; i < ivoI.size(); i++)
    {
        QDomNode n = ivoI.at(i);


        int ii = n.toElement().attribute("ivo").toInt();
        QDomNodeList lst= n.childNodes();

        for(int k=0;k<lst.count();k++)
        {
            QDomNode nd = lst.at(k);
            int io = nd.toElement().attribute("ivo").toInt();

            QDomNodeList lstState= nd.childNodes();

            for(int jj=0;jj<lstState.count();jj++)
            {
                qDebug()<<lstState.at(jj).toElement().text().toInt();
                //само заполнение массива
                tableIvo->array[ii][io].append(lstState.at(jj).toElement().text().toInt());
            }
        }
    }

    //закрываем файл
    file.close();

    return tableIvo;
}


TableTvo* DispatcherTable::ReadTvo(const char* fileTvo)                     //Чтение xml-файла с таблицей ТВО
{
    QDomDocument doc;
    QFile file(fileTvo);
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return NULL;

    qDebug()<<"badger_2";


    TableTvo* tableTvo = new TableTvo;
    const int countLevel = 4;                     //максимальная глубина ТВО

    QDomNodeList lvl = doc.elementsByTagName("level");

    ElTvoLst* lastEl;
    int n_ar;
    int max_number = -1;


    //строим дерева из xml-файла
    QList<ElTvoLst*> lst[countLevel];

    for (int i = 0; i < lvl.size(); i++)
    {
        QDomElement dEl = lvl.at(i).toElement();
        n_ar=dEl.attribute("l").toInt();
        if(n_ar==0)
        {
            lastEl = new ElTvoLst;
            lastEl->value = dEl.attribute("v").toInt();
            lastEl->parent = NULL;
            lst[n_ar].append(lastEl);
        }
        else
        {
            lastEl = new ElTvoLst;
            lastEl->value = dEl.attribute("v").toInt();
            lastEl->parent = lst[n_ar-1].last();
            lst[n_ar].append(lastEl);
        }

        if(lastEl->value > max_number)
        {
            max_number = lastEl->value;
        }
    }

    file.close();


    //преобразуем дерево в массив
    tableTvo->countTvo = max_number+1;
    tableTvo->arrayTvo = new ElTvo*[tableTvo->countTvo];

    for(int i=0;i<tableTvo->countTvo;i++)
    {
        tableTvo->arrayTvo[i] = NULL;
    }

    for(int i=0;i<countLevel;i++)
    {
        for(int j=0;j<lst[i].count();j++)
        {
            int number = lst[i].at(j)->value;
            ElTvo * cur_tvo = tableTvo->arrayTvo[number] = new ElTvo;
            cur_tvo->numberCurrentLevel = i;
            cur_tvo->arrayLevelValue = new int[cur_tvo->numberCurrentLevel+1];

            ElTvoLst* next;
            for(int k=i;k>-1;k--)
            {
                //именно заполнение массива
                if(k==i)
                {
                    cur_tvo->arrayLevelValue[k] = number;
                    next = lst[i].at(j)->parent;
                }
                else
                {
                    cur_tvo->arrayLevelValue[k] = next->value;
                    next = next->parent;
                }
            }
        }
    }

    //очистка памяти из-под дерева
    for(int i=0;i<countLevel;i++)
    {
        while(lst[i].count()>0)
        {
            delete lst[i].at(0);
            lst[i].pop_front();
        }
    }

    return tableTvo;
}


TableIvoTvo* DispatcherTable::ReadIvoTvo(const char* fileIvoTvo)                    //Чтение xml-файла противоречий ИВО-ТВО
{
    QDomDocument doc;
    QFile file(fileIvoTvo);
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return NULL;


    //вычисляем максимальный ТВО
    QDomNodeList tvo = doc.elementsByTagName("tvo");
    int max_elT = -1;    //максимальный tvo-элемент массива
    int max_elI = -1;    //максимальный ivo-элемент массива
    int cur_valT, cur_valI;
    for (int i = 0; i < tvo.size(); i++)
    {
        cur_valT = tvo.at(i).toElement().attribute("tv").toInt();
        if (cur_valT > max_elT)
        {
            max_elT = cur_valT;
        }
    }

    QDomNodeList lst= tvo.at(0).childNodes();


    //вычисляем максимальный ИВО
    for(int k=0;k<lst.count();k++)
    {
        QDomNode nd = lst.at(k);
        cur_valI = nd.toElement().attribute("iv").toInt();
        if (cur_valI > max_elI)
        {
            max_elI = cur_valI;
        }
    }



    TableIvoTvo* tableIvoTvo = new TableIvoTvo;
    tableIvoTvo->countTvo = max_elT+1;
    tableIvoTvo->countIvo = max_elI+1;


    //выдаем память под массив
    tableIvoTvo->array = new int*[tableIvoTvo->countTvo];
    for(int i=0;i<tableIvoTvo->countTvo;i++)
    {
        tableIvoTvo->array[i] = new int[tableIvoTvo->countIvo];
    }

    //читая xml-файл, запоняем массив
    for (int i = 0; i < tvo.size(); i++)
    {
        QDomNode n = tvo.at(i);

        int tv = n.toElement().attribute("tv").toInt();
        QDomNodeList lst= n.childNodes();

        for(int k=0;k<lst.count();k++)
        {
            QDomNode nd = lst.at(k);
            int iv = nd.toElement().attribute("iv").toInt();
            int st = nd.toElement().attribute("state").toInt();
            //именно заполнение массива
            tableIvoTvo->array[tv][iv] = st;
        }
    }

    file.close();

    return tableIvoTvo;
}
}
