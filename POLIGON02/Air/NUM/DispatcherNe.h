#ifndef ARRAYUNINUM_H
#define ARRAYUNINUM_H

//класс работающий с едиными номерами

#include <QList>
#include <QFile>
#include <QTextStream>

namespace N_U_M
{
class DispatcherNe
{
public:

    DispatcherNe(){}
    void Init(int* countNe,int* shift);             //инициализация класса, отвечающего за присвоения Ne

    void FreeNe(int ne);                            //освободить Ne
    int SetNe(int numberArray);                     //установить Ne
                                                    //-1 - все элементы заняты
    bool IsOurNe(int ne);                           //мы ли присваивали Ne?


    //getter
    int GetCountNe(int number);                     //кол-во элементов в подмассиве
    QList<int> GetSeqFreeNe(int number);            //получить следующий свободный номер в подмассиве

    int GetBeginInterval(int n);                    //получать начало интервала в зависимости от номера подмассива
    int GetEndInterval(int n);                      //получать конец интервала в зависимости от номера подмассива

private:

    int countNe[2];                                 //количество элементов в подмассиве
    int  shift[2];                                  //сдвиги

    int intervalAllBegin[2];                        //массив начал подмассивов
    int intervalAllEnd[2];                          //массив концов подмассивов

    QList<int> seqFreeNe[2];                        //последовательность присвоения Ne
};
}

#endif // ARRAYUNINUM_H
