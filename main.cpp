#include <iostream>
#include "Problema_2_1.h"
#include "Unidades.h"

using namespace std;

int main()
{
    //Problema 2.3
    /*Aire fluyendo en un túnel de viento a 0.3 atm y -100°C*/
    /*Cuál es la densidad del aire? Cuál es el volumen específico*/

    auto temp = 173._celsius;
    auto presion = 0.3_atm;

    //p=roRT

   auto ro = presion/(R_aire*temp);

    cout << "presion: " << presion << " temperatura: " << temp << endl;
    cout << "densidad: " << ro << endl;
    cout << "volumen especifico: " << 1/ro << endl;

    return 0;
}
