//Autor: Roberto Cantu Reyes A01196704
//Fecha de creacion 22/10/2021
//Fecha de modificacion 22/10/2021
//Este es el archivo que se encarga de calcualr el intervalo de predicion al 70%
#include <math.h>
class Interval{
    private:
    double sigma(int n, double sum);
   
    public:
    Interval(); //Constructor
    double calcRange(double, int , double , double , double , double);

};

Interval::Interval(){

}

//Recibe como parametro el valor de x para una distribucion de n-2 grados
//de libertad donde p=0.5, recibe n que es la cantidad de parejas de datos leidas
//, recibe el coeficiente de correlacion xk, recible el promedio de x, recibe la sumatoria
//de (yi -B0 - B1xi)^2 y por ultimo recibe la sumatoria de la diferencia de (xk-xAvg)^2
//Retorna como resultado el intervalo de prediccion 
//.i
double Interval::calcRange(double x, int n, double xk, double avgX, double sumYBX, double sumXdif){
        return x * sigma(n,sumYBX) * sqrt(1.0+(1.0/n) + (pow(xk-avgX,2) / sumXdif));    
    }

//Recibe como parametro n la cantidad de parejas de datos leidas,
//y la sumatoria de la diferencia de (xk-xAvg)^2
//Retorna el valor de sigma 
//.i
double Interval::sigma(int n, double sum){
    return sqrt((1.0/(n-2)) * sum);
}

