//Autor: Roberto Cantu Reyes A01196704
//Fecha de creacion 05/11/2021
//Fecha de modificacion 05/11/2021
//Esta es el archivo que almacena los resultados
//de la regresion multiple
#include <string>
#include <vector>
#include "Tuple.h"
#include "Gauss.h"
using namespace std;
class MultipleRegression {
    private:
    double n;
    double wk;
    double xk;
    double yk;
    double zk;
    double b0;
    double b1;
    double b2;
    double b3;
    double sumW;
    double sumX;
    double sumY;
    double sumZ;
    double sumW2;
    double sumWX;
    double sumWY;
    double sumWZ;
    double sumX2;
    double sumXY;
    double sumXZ;
    double sumY2;
    double sumYZ;
    vector<Tuple> tuples;

    public:
    MultipleRegression();
    void setTuple(string);
    void calcTuples();
    double getN();
    double getWk();
    double getXk();
    double getYk();
    double getZk();
    double getB0();
    double getB1();
    double getB2();
    double getB3();

};

//Constructor
MultipleRegression::MultipleRegression(){
    n = 0;
    wk = 0;
    xk = 0;
    yk = 0;
    zk = 0;
    b0 = 0;
    b1 = 0;
    b2 = 0;
    b3 = 0;
    sumW = 0;
    sumX = 0;
    sumY = 0;
    sumZ = 0;
    sumW2 = 0;
    sumWX = 0;
    sumWY = 0;
    sumWZ = 0;
    sumX2 = 0;
    sumXY = 0;
    sumXZ = 0;
    sumY2 = 0;
    sumYZ = 0;
}

//Getters
double MultipleRegression::getN(){
    return n;
}

double MultipleRegression::getWk(){
    return wk;
}

double MultipleRegression::getXk(){
    return xk;
}

double MultipleRegression::getYk(){
    return yk;
}

double MultipleRegression::getZk(){
    return zk;
}

double MultipleRegression::getB0() {
    return b0;
}

double MultipleRegression::getB1(){
    return b1;
}

double MultipleRegression::getB2(){
    return b2;
}

double MultipleRegression::getB3(){
    return b3;
}

//Recibe una linea del archivo como string
//Se encarga de crear la tupla y meterla en
//el vector de tuplas
//.i
void MultipleRegression::setTuple(string sLine){
    Tuple currLine;
    int posInit = 0;
    int posFound = 0;
    bool firstLap = true;
    string splitted;
    vector<string> results;

    while (posFound >=0){
        posFound = sLine.find(",", posInit);
        splitted = sLine.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        results.push_back(splitted);
    }
    if(results.size() == 3 && firstLap){
        wk = stod(results[0]);
        xk = stod(results[1]);
        yk = stod(results[2]);
        firstLap = false;
        
    }
    else if(results.size() > 4){
        cout << "Los elementos del archivo no se encuentran en el formato requerido" << endl;
        exit(1);
    } else {
        currLine.setW(stod(results[0]));
        currLine.setX(stod(results[1]));
        currLine.setY(stod(results[2]));
        currLine.setZ(stod(results[3]));
        tuples.push_back(currLine);
    } 
}

//Este metodo no recibe parametros de entrada
//La funcion de este metodo es realizar todos los calculos necesarios
//con el vector de tuplas para la regresion multiple
//.i
void MultipleRegression::calcTuples(){
    n = tuples.size();
    for(int i=0; i < n ; i++){ 
      sumW += tuples[i].getW();
      sumX += tuples[i].getX();
      sumY += tuples[i].getY();
      sumZ += tuples[i].getZ();
      sumW2 += tuples[i].getW() * tuples[i].getW();
      sumWX += tuples[i].getW() * tuples[i].getX();
      sumWY += tuples[i].getW() * tuples[i].getY();
      sumWZ += tuples[i].getW() * tuples[i].getZ();
      sumX2 += tuples[i].getX() * tuples[i].getX();
      sumXY += tuples[i].getX() * tuples[i].getY();
      sumXZ += tuples[i].getX() * tuples[i].getZ();
      sumY2 += tuples[i].getY() * tuples[i].getY();
      sumYZ += tuples[i].getY() * tuples[i].getZ();
        
    }
   //Creacion del sistema de ecuaciones en una matriz
   double matA [4][5] = {{n,sumW,sumX,sumY,sumZ}, {sumW,sumW2,sumWX,sumWY,sumWZ},
   {sumX,sumWX,sumX2,sumXY,sumXZ}, {sumY,sumWY,sumXY,sumY2,sumYZ}};

   //Creacion del objeto de Gauss
   Gauss g;
   vector<double> result;
   g.gaussElimination(4,5,matA);
   result = g.getResult();
   b0 = result[0];
   b1 = result[1];
   b2 = result[2];
   b3 = result[3];
   zk = b0 + wk * b1 + xk * b2 + yk * b3;
}