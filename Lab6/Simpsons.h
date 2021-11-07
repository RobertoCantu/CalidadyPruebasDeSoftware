//Autor: Roberto Cantu Reyes A01196704
//Fecha de creacion 25/09/2021
//Fecha de modificacion 15/10/2021
//Este es el archivo que se encarga de realizar la integral
//mediante el metodo de simpsons
#include <iostream>
#include <math.h>
#include <stdlib.h> 
# define PI 3.14159265358979323846

//.b=60
class Simpsons{
    private:
    int numSeg; //Must be an even number
    double acceptableError;
    double oldResult;
    double newResult;
    double gamma(double);
    double tDistribution(double, int);
    bool firstTime = false;
    
    public:
    Simpsons(); //Constructor 
    double simpsonsRule(double,int);


};
//Constructor
Simpsons::Simpsons(){ 
    numSeg = 100;
    acceptableError = 0.000000001;
    oldResult = 0.0;
    newResult = 0.0;
}

//Recibe como parametro un numero de tipo doble
//Se encarga de calcular el valor de gamma
//Retorna como resultado el valor de gamma 
//.i
double Simpsons::gamma(double num){
    if(num == 1){
        return 1.0;
    }
    else if(num == 0.5){
        return sqrt(PI);
    } else {
        return (num-1.0)*gamma(num - 1.0);
    }

}

//Recibe como parametro el valor de x y dof que es el grado de libertad
//Se encarga de calcular el resultado de la distribucion t
//Retorna como resultado el valor de la distribucion t
//.i
double Simpsons::tDistribution(double x, int dof){
    return (gamma((dof+1.0) / 2.0) / (pow((dof * PI),0.5) * gamma(dof/2.0))) * pow((1.0 + (pow(x,2.0) / dof)),-(dof+1.0) / 2.0 );
}

//Recibe como parametro el valor de x y dof que es el grado de libertad
//Se encarga de calcular la integral mediante el metodo de simpson utilizando recursividad
//Retorna como resultado la probablidad 
//.i
double Simpsons::simpsonsRule(double x, int dof){
    int i = 1;
    double w = x / numSeg;
    double sumImpair = 0.0;
    double sumPair = 0.0;
    double tempResult = 0.0;

    for (i; i < numSeg; i++){
        if (i % 2 == 0){
            sumPair += tDistribution( i * w, dof);
        } else {
            sumImpair += tDistribution( i * w, dof);
        }
    }
    
    tempResult = (tDistribution(0.0,dof) + 4.0 * sumImpair + 2.0 * sumPair + tDistribution(i*w,dof)) * w / 3.0;
   
    if (oldResult == 0 && firstTime == false){
        firstTime = true;
        oldResult = tempResult;
    }
    //Recursion
    if (abs(oldResult - newResult) < acceptableError){
        return newResult;
    }
    else if(newResult > 0 && abs(oldResult - newResult) > 0){
        oldResult = newResult;
        newResult = tempResult;
        numSeg *= 2;
        return simpsonsRule(x,dof);
    }

    if (oldResult == 0 && newResult == 0){
        oldResult = tempResult;
        numSeg *= 2;
        return simpsonsRule(x,dof);
    }

    if (oldResult > 0 && newResult == 0){
        newResult = tempResult;
        numSeg *= 2;
        return simpsonsRule(x,dof);
    }
}