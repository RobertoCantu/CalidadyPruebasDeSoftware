// Autor: Roberto Cantu Reyes A01196704
// Fecha de creacion 2/10/2021
// Fecha de modificacion 08/10/2021
// Este es el archivo que se encarga de encontrar el valor de X dada la probabiliadd
#include <stdlib.h>
//.b=71
class CalculateX {
    private:
        double x;
        double acceptableError;
        double d;
        double integralResult;
        bool startLap;
        bool end;
        bool rightDirection;
        bool leftDirection;
        double p;
        double dof;
        double oldP;

    public:
        CalculateX( double,double); //Constructor 
        double findX();


};

//Constructor
CalculateX::CalculateX( double p, double dof){
    x = 1;
    acceptableError = 0.000000001;
    d = x /2;
    integralResult = 0;
    startLap = true;
    end = false;
    rightDirection = false;
    leftDirection = false;
    this->p = p;
    this->dof = dof;
    oldP = 0;
    
}

//No tiene parametros
//Este metodo se encarga de encontrar el valor de x para cierta probabildiad con 
//ciertos grados de libertad de manera recursiva
//Retorna como resultado el valor de x 
//.i
 double CalculateX::findX(){
    //Use of the object Simpsons simpsonsrule method
    Simpsons integral;
    integralResult = integral.simpsonsRule(x,dof);

    //Load results in the first recursion call
    if (startLap){
        startLap = false;
        if (integralResult < p){
            oldP = integralResult;
            x = x + d;
            rightDirection = true;
            return findX();
        } else if(integralResult > p) {
            oldP = integralResult;
            x = x - d;
            leftDirection = true;
            return findX();
        }
    }
    else if (!startLap){  
        if (integralResult < p){
            //Condition for rightDirection flag
            if(!rightDirection){             
                d = d / 2;
                x = x + d;
                rightDirection = true;
                leftDirection = false;
            } else {
                x = x + d;
            }
            //Compare if last result vs result meet AcceptableError condition
            if (abs(oldP - integralResult) < acceptableError){
                return x;
            } else {
                oldP = integralResult;
                return findX();
            }
        }
        else if(integralResult > p){
            //Condition for left direction Flag
            if (!leftDirection){          
                d = d / 2;
                x = x - d;
                leftDirection = true;
                rightDirection = false;
            } else {
                x = x - d;
            }
            //Compare if last result vs result meet AcceptableError condition
             if (abs(oldP - integralResult) < acceptableError){
                return x;
            } else {
                oldP = integralResult;
                return findX();
            }
        }    
    }
}
