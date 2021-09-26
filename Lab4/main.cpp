#include <iostream>
#include "PrintResults.h"
#include "StatisticalAnalysis.h"

using namespace std;

int main(){
    double x;
    int dof;
    double probability;

    cout << "Ingresa el valor de x: " << endl;
    cin >> x;
    if (x < 0){
        cout << "Valor incorrecto para x imposible realizar la integral" << endl;
        exit(1);
    }
    cout << "Ingresa el valor de dof: " << endl;
    cin >> dof;
    if (dof <= 0){
        cout << "Valor incorrecto para dof imposible realizar la integral" << endl;
        exit(1);
    }

    //Calculate Integral
    StatisticalAnalysis integral;
    probability = integral.simpsonsRule(x,dof);
    
    //Print results
    PrintResults finalResults(x,dof,probability);
    finalResults.print();
    return 0;
}