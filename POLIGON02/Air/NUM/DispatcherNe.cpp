#include "DispatcherNe.h"

namespace N_U_M
{
//инициализация класса, отвечающего за присвоения Ne
void DispatcherNe::Init(int* countNe,int* shift)
{
    for(int i=0;i<2;i++)
    {
        this->shift[i] = shift[i];
        this->countNe[i] = countNe[i];

        for(int j=0;j<countNe[i];j++)
        {
            seqFreeNe[i].append(j);        //добавляем все свободные Ne в список свободных номеров
        }
    }

    for(int i = 0;i<2;i++)
    {
        intervalAllBegin[i] = shift[i*2+2];
        intervalAllEnd[i] = shift[i*2+2+1];
    }
}

//получать начало интервала в зависимости от номера подмассива
int DispatcherNe::GetBeginInterval(int n)
{
    return intervalAllBegin[n];
}

//получать конец интервала в зависимости от номера подмассива
int DispatcherNe::GetEndInterval(int n)
{
    return intervalAllEnd[n];
}


bool DispatcherNe::IsOurNe(int ne)           //мы ли присваивали Ne?
{
    for(int i=0;i<2;i++)
    {
        if((ne>=shift[i]) && (ne<countNe[i]+shift[i]))
        {
            return true;
        }
    }

    return false;
}


void DispatcherNe::FreeNe(int ne)           //освободить Ne
{
    for(int i=0;i<2;i++)
    {
        if((ne>=shift[i]) && (ne<countNe[i]+shift[i]))
        {
            int numOnArray = ne - shift[i];
            seqFreeNe[i].append(numOnArray);
            break;
        }
    }
}



int DispatcherNe::SetNe(int numberArray)             //установить Ne
{
    if(numberArray == -1)
        return 0;

    int new_ne = seqFreeNe[numberArray].first()+shift[numberArray];
    seqFreeNe[numberArray].pop_front();
    return new_ne;
}

//getter
int DispatcherNe::GetCountNe(int number)                 //кол-во элементов в подмассиве
{
    return countNe[number];
}

QList<int> DispatcherNe::GetSeqFreeNe(int number)        //получить следующий свободный номер в подмассиве
{
    return seqFreeNe[number];
}

}
