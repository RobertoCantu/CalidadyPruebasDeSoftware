#include <iostream>
#include "PrintResults.h"
#include "CalculateX.h"

using namespace std;
//.b=23
//.i
int main(){
    double x;
    double dof;
    double probability;

    cout << "Ingresa el valor de p: " << endl; //.m
    cin >> probability;
    if (probability <= 0 || probability >= 0.5){ //.m
        cout << "Valor incorrecto para p imposible encontrar el valor de x" << endl;
        exit(1);
    }
    cout << "Ingresa el valor de dof: " << endl;
    cin >> dof;
    if (dof <= 0){
        cout << "Valor incorrecto para dof imposible encontrar el valor de x" << endl;
        exit(1);
    }

    //Find value of x 
    CalculateX findX(probability,dof); //.m
    x = findX.findX(); //.m
    
    //Print results
    PrintResults finalResults(x,dof,probability);
    finalResults.print();
    return 0;
}