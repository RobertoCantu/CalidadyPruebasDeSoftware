//Autor: Roberto Cantu Reyes A01196704
//Fecha de creacion 21/08/2021
//Fecha de modificacion 05/11/2021
//Este es el archivo principal del programa 
#include <iostream>
#include "ReadFile.h"
using namespace std;

//.b=9
int main(){
    
    string fileName;  
    cout <<"Ingresa el nombre del archivo" << endl;
    cin >> fileName;
    ReadFile obj(fileName);
    return 0;

}