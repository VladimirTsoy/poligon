#ifndef EMUN_H
#define EMUN_H

#include <QList>

namespace N_U_M
{
enum NumTvo
{
    NUM_TVO_RT = 1,             //ракета
    NUM_TVO_PN = 2,             //самолет
    NUM_TVO_CA = 5              //косм.ап.
};

//таблица результирующего ИВО по ИВО источника и обоб.трассы
struct TableIvo
{
    int count;                          //общее кол-во ИВО
    QList<int>** array;                 //[источник][обобщенная трасса] = результирующее ИВО

};



struct ElTvoLst                         //для построения дерева ТовВО из xml-файла
{
    ElTvoLst* parent;
    int value;
};


struct ElTvo
{
    int numberCurrentLevel;             //номер текущего уровня
    int* arrayLevelValue;               //значения на уровнях (по данному ТВО)
};


struct TableTvo                         //таблица ТВО, считанная из файла
{
    int countTvo;                       //общее кол-во ТВО
    ElTvo** arrayTvo;//[tvo] (ElTvo*)   //все возможные ТВО (там где ТВО нет - там NULL)

};


struct TableIvoTvo                  //таблица противоречий ИВО - ТВО
{
    int countTvo;                   //размерность ТВО
    int countIvo;                   //размерность ИВО
    int** array;                    //[ТВО][ИВО]
                                    // = 1 - противоречия нет
                                    // = -1 - противоречие
};

struct TableNum                     //все таблицы принятий решений
{
    struct TableIvo* tableIvo;
    struct TableTvo* tableTvo;
    struct TableIvoTvo* tableIvoTvo;
};



}


#endif // EMUN_H

