#pragma once
#include "Unidades.h"

/*De la ecuaci�n 2.3, sabemos que p = den*R*T, por lo que T = p/(den*R) */
/*necesitas un s�mbolo para ro (densidad)*/

/*regresa presi�n*/
double eq2_3p (double den, double T);
double eq2_3t(double den, double p);

/*Vas a escribir un vergo de ecuaciones en el transcurso de este proyecto, hay manera de "completar" patrones?
 *Si s� que existe una relaci�n directa entre presi�n, densidad, la constante R y Temperatura, no hay una manera
 * de rellenar el par�metro faltante? Estoy seguro de que con templates se podr�a hacer, especificando la ecuaci�n
 * y pasando los tipos que actualmente tienes como par�metros template a la funci�n. Eso estar�a cool */


