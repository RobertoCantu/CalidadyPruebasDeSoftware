//Autor: Roberto Cantu Reyes A01196704
//Fecha de creacion 22/10/2021
//Fecha de modificacion 22/10/2021
//Este es el archivo que calcula la significancia de cierta correlacion 
#include <stdlib.h> 
#include <math.h>
#include "Simpsons.h"
class Significance {

    private:
    double calcX(double, int, double );
    double calcP(double,int);

    public:
    Significance(); //Constructor
    double calcSignificance(double,int,double);



};
//Constructor 
Significance::Significance(){

}

//Recibe como parametro los coeficientes de correlacion
// r y r2, y n la cantidad de parejas leidas
//Se encarga de calcualr el valor de x
//Retorna como resultado el valor de x
//.i
double Significance::calcX(double r, int n, double r2){
    
    return (abs(r) * sqrt(n-2) ) / sqrt(1-r2);
}

//Recibe como parametro el valor de x y dof los grados de libertad
//Se encarga de calcular la probabilidad de x y dof
//mediante el metodo de simpsons
//Regresa como resultado la probabilidad
//.i
double Significance::calcP(double x, int dof ){
    Simpsons integral;
    return integral.simpsonsRule(x,dof);
}

//Recibe como parametro los coeficientes de correlacion 
// r y r2, y n la cantidad de parejas leidas
//Se encarga de calcular la significancia para esos valores
//Retorna como reusltado el valor de la significancia 
//.i
double Significance::calcSignificance(double r,int n, double r2){
    return 1 - 2 * calcP(calcX(r,n,r2),n-2 );
}
