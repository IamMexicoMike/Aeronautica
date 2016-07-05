#pragma once
#include "Unidades.h"

/*De la ecuación 2.3, sabemos que p = den*R*T, por lo que T = p/(den*R) */
/*necesitas un símbolo para ro (densidad)*/

/*regresa presión*/
double eq2_3p (double den, double T);
double eq2_3t(double den, double p);

/*Vas a escribir un vergo de ecuaciones en el transcurso de este proyecto, hay manera de "completar" patrones?
 *Si sé que existe una relación directa entre presión, densidad, la constante R y Temperatura, no hay una manera
 * de rellenar el parámetro faltante? Estoy seguro de que con templates se podría hacer, especificando la ecuación
 * y pasando los tipos que actualmente tienes como parámetros template a la función. Eso estaría cool */


