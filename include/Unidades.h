#pragma once

#include <iostream>

/*Las unidades fundamentales no necesitan otras unidades para definirse*/
/*Según Strstrp, el valor de las unidades está codificado en el tipo*/
/*Una unidad está diseñada para uso en tiempo de compilación*/
/*Necesitamos definir todas las unidades fundamentales
Masa, distancia, tiempo, temperatura

*/
template <int Masa, int Distancia, int Tiempo, int Temperatura>
struct Unidad
{
    enum {masa=Masa, distancia=Distancia, tiempo=Tiempo, temperatura=Temperatura};
};

/*Proveemos notaciones convencionales para los tipos de unidades más comunes*/
/*Los valores negativos indican presencia como divisor*/
/*--------------Unidades fundamentales-----------------*/
using kg = Unidad<1,0,0,0>; //Masa - Kilogramos
using m = Unidad<0,1,0,0>; //Distancia - metros
using s = Unidad<0,0,1,0>; //Tiempo - segundos
using K = Unidad<0,0,0,1>; //Temperatura -> Kelvin
/*--------------Unidades derivadas-----------------------*/
using v = Unidad<0,1,-1,0>; //Velocidad - metros por segundo (m/s)
using a = Unidad<0,1,-2,0>; //Aceleración - metros por segundos cuadrados(m/s*s)
using N = Unidad<1,1,-2,0>; //Fuerza - Newton
using Pa = Unidad<1,-1,-2,0>; //Presión - Pascales (N/m2). Faltan Atm(1.01x1e5Pa)
using Kgpm3 = Unidad<1,-3,0,0>; //Densidad - Kilogramos por metro cúbico
using m3 = Unidad<0,3,0,0>; //Volumen - metros cúbicos
using J = Unidad<1,2,-2,0>; //Energía - Joules
using R = Unidad<0,2,-2,-1>; //R - Unidad de las constantes de los gases

/*--------------- Suma_Unidad y Resta_Unidad son funciónes de tipo en Unidades ----------------------------*/

/*Cuando multiplicamos dos Cantidades, sus unidades se suman. Por ende, la suma de Unidades es útil*/
template<typename U1, typename U2>
struct SumarU
{
    using tipo = Unidad<U1::masa+U2::masa, U1::distancia+U2::distancia, U1::tiempo+U2::tiempo, U1::temperatura+U2::temperatura>;
};

template<typename U1, typename U2>
using Suma_Unidad = typename SumarU<U1, U2>::tipo;

/*Similarmente, dividir dos Cantidades resta sus unidades*/
/*Cuando multiplicamos dos Cantidades, sus unidades se suman. Por ende, la suma de Unidades es útil*/
template<typename U1, typename U2>
struct RestarU
{
    using tipo = Unidad<U1::masa-U2::masa, U1::distancia-U2::distancia, U1::tiempo-U2::tiempo, U1::temperatura-U2::temperatura>;
};

template<typename U1, typename U2>
using Resta_Unidad = typename RestarU<U1, U2>::tipo;

/*---------------------------------------------------------------------------------------------------------------------------*/

/*explicit es para evitar las conversiones explícitas de entidades adimensionales*/

template <typename T>
struct Cantidad
{
    double val;
    explicit constexpr Cantidad(double d): val{d} {}
};

/*Según Strstrp, podríamos haber incurrido en mayor finesse si usásemos un parámetro template para
representar el tipo del valor, en lugar de double*/

/*Sólo podemos sumar y restar valores con las mismas Unidades*/

template <typename U>
Cantidad<U> operator+(Cantidad<U> x, Cantidad<U> y)
{
    return Cantidad<U>{x.val + y.val};
}

template <typename U>
Cantidad<U> operator-(Cantidad<U> x, Cantidad<U> y)
{
    return Cantidad<U>{x.val - y.val};
}

/*El constructor de Cantidad es explícito, por lo que necesitábamos convertir el double resultante a Cantidad<U>*/

/*La multiplicación de Cantidades requiere la suma de sus Unidades, y la división, la resta de ellas*/
/*por supuesto, también requiere multiplicar sus magnitudes*/
template<typename U1, typename U2>
Cantidad<Suma_Unidad<U1, U2>> operator*(Cantidad<U1> x, Cantidad<U2> y)
{
    return Cantidad<Suma_Unidad<U1, U2>>{x.val*y.val};
}

template<typename U1, typename U2>
Cantidad<Resta_Unidad<U1, U2>> operator/(Cantidad<U1> x, Cantidad<U2> y)
{
    return Cantidad<Resta_Unidad<U1, U2>>{x.val/y.val};
}


/*Dadas estas definiciones, podemos expresar la mayoría de las computaciones.
Nos hacen falta operaciones por escalares:
Podríamos usar Cantidad<Unidad<0,0,0,0>>(valor)

Podemos proveer una conversión implícita de double a Cantidad<Unidad<0,0,0,0>> o añadir unas variantes
a nuestras operaciones aritméticas:
*/

template <typename U>
Cantidad<U> operator*(Cantidad<U> x, double y)
{
    return Cantidad<U>{x.val*y};
}

template <typename U>
Cantidad<U> operator*(double y, Cantidad<U> x)
{
    return Cantidad<U>{x.val*y};
}

template <typename U>
Cantidad<U> operator/(Cantidad<U> x, double y)
{
    return Cantidad<U>{x.val/y};
}

template <typename U>
Cantidad<U> operator/(double y, Cantidad<U> x)
{
    return Cantidad<U>{y/x.val};
}

/*La principal razón para no definir una conversión explícita de double a Cantidad<0,0,0,0> es porque
no queremos que las conversiones sucedan para sumas o restas:
Cantidad<v> velocidad{5.34};
auto velociad_incrementada = 2.3 + velocidad //error: no podemos añadir un escalar a una velocidad*/

/*Literales de Unidades*/
/*Distancia - metros*/
constexpr Cantidad<m> operator"" _m(long double d) {return Cantidad<m>{static_cast<double>(d)};}
constexpr Cantidad<m> operator"" _mm(long double d) {return Cantidad<m>{static_cast<double>(d/1e3)};}
constexpr Cantidad<m> operator"" _um(long double d) {return Cantidad<m>{static_cast<double>(d/1e6)};}
constexpr Cantidad<m> operator"" _nm(long double d) {return Cantidad<m>{static_cast<double>(d/1e6)};}
constexpr Cantidad<m> operator"" _km(long double d) {return Cantidad<m>{static_cast<double>(d*1e3)};}

constexpr Cantidad<s> operator"" _s(long double d) {return Cantidad<s>{static_cast<double>(d)};}
constexpr Cantidad<kg> operator"" _kg(long double d) {return Cantidad<kg>{static_cast<double>(d)};}
constexpr Cantidad<K> operator"" _K(long double d) {return Cantidad<K>{static_cast<double>(d)};}
constexpr Cantidad<K> operator"" _celsius(long double d) {return Cantidad<K>{static_cast<double>(d+273)};}
constexpr Cantidad<Kgpm3> operator"" _kgpm3(long double d) {return Cantidad<Kgpm3>{static_cast<double>(d)};}
constexpr Cantidad<m3> operator"" _m3(long double d) {return Cantidad<m3>{static_cast<double>(d)};} //metros cúbicos
constexpr Cantidad<Pa> operator"" _pa(long double d) {return Cantidad<Pa>{static_cast<double>(d)};}
constexpr Cantidad<Pa> operator"" _atm(long double d) {return Cantidad<Pa>{static_cast<double>(d*1.01e5)};}

/*Constantes*/
const Cantidad<R> R_aire(287.0); //Constante de gas específico del aire [J/(kg*K)]

/*Para terminar, necesitamos el operator de igualdad, y el operador de salida*/
/*Observemos que las cantidades se pasan por valor. En runtime son representadas como double, por eso no hay
overhead. Qué hay de vector<Cantidad<U>>?*/
template<typename U>
constexpr Cantidad<Suma_Unidad<U,U>> cuadrado(Cantidad<U> x)
{
    return Cantidad<Suma_Unidad<U,U>>(x.val*x.val);
}

template <typename U>
bool operator==(Cantidad<U> x, Cantidad<U> y)
{
    return x.val==y.val;
}

template <typename U>
bool operator!=(Cantidad<U> x, Cantidad<U> y)
{
    return x.val!=y.val;
}

std::string sufijo(int u, const char* x); //función de ayuda, prototipo

template<typename U>
std::ostream& operator<<(std::ostream& os, Cantidad<U> v)
{
    return os << v.val << sufijo(U::masa, "kg") << sufijo(U::distancia, "m") << sufijo(U::tiempo, "s") << sufijo(U::temperatura, "K");
}
