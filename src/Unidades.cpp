#include "Unidades.h"

std::string sufijo(int u, const char* x) //función de ayuda
{
    std::string suf;
    if(u)
    {
        suf += x;
        if (u>1)
            suf+='0'+u;

        if(u<0)
        {
            suf += '-';
            suf += '0'-u;
        }
    }
    return suf;
}
