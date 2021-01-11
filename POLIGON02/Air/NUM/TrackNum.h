#ifndef ELEMENTNUM_H
#define ELEMENTNUM_H


#include "S_E_Num.h"
#include <QString>
#include "TrcNum.h"

//данные по обобщенной трассе и НУМ (для промежуточного состояния)


namespace N_U_M
{
class TrackNum: public TrcNum
{
public:
    TrackNum();

    //getter
    int GetIvo();
    int GetTvo();
    int GetNe();


    //setter
    void SetIvo(int ivo);
    void SetTvo(int tvo);
    void SetNe(int ne);


private:
    int ivo;
    int tvo;
    int ne;
};
}

#endif // ELEMENTNUM_H
