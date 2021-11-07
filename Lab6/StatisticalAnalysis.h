//Autor: Roberto Cantu Reyes A01196704
//Fecha de creacion 14/09/2021
//Fecha de modificacion 22/10/2021
//Este es el archivo que se encarga de almacenar todos los calculos estadisticos
#include <vector>
#include "Tuple.h"
#include "Significance.h"
#include "Interval.h"
#include "CalculateX.h"
#include <string>
#include <math.h>
using namespace std;

//.b=106;
class StatisticalAnalysis {
    private:
        double n;
        double xk;
        double r;
        double r2;
        double b0;
        double b1;
        double yk;
        double sig;
        double range;
        double upi;
        double lpi;
        double sumX;
        double sumY;
        double avgX;
        double avgY;
        double sumX2;
        double sumY2;
        double sumXY;
        vector<Tuple> tuples;
        void calcB1();
        void calcRXY();
        void calcR2();
        void calcB0();
        void calcYk();

    public:
        StatisticalAnalysis();
        double getN();
        double getXk();
        double getR();
        double getR2();
        double getB0();
        double getB1();
        double getYk();
        double getSig();
        double getRange();
        double getUpi();
        double getLpi();
        void setXk(double);
        void setTuple(string);
        void calcTuples();
};

//Constructor
StatisticalAnalysis::StatisticalAnalysis(){
    n = 0.0;
    xk = 0.0;
    r = 0.0;
    r2 = 0.0;
    b0 = 0.0;
    b1 = 0.0;
    yk = 0.0;
    sig = 0.0;
    range = 0.0;
    upi = 0.0;
    lpi = 0.0;
    sumX = 0.0;
    sumY = 0.0;
    sumX2 = 0.0;
    sumY2 = 0.0;
    sumXY = 0.0;
}

//Getters and Setters
void StatisticalAnalysis::setXk(double xk){
    this->xk = xk;
}

 double StatisticalAnalysis::getN(){
    return n;
}

 double StatisticalAnalysis::getXk(){
    return xk;
}

 double StatisticalAnalysis::getR(){
    return r;
}

 double StatisticalAnalysis::getR2(){
    return r2;
}

 double StatisticalAnalysis::getB0(){
    return b0;
}

 double StatisticalAnalysis::getB1(){
    return b1;
}

 double StatisticalAnalysis::getYk(){
    return yk;
}

double StatisticalAnalysis::getSig(){
    return sig;
}
double StatisticalAnalysis::getRange(){
    return range;
}
double StatisticalAnalysis::getUpi(){
    return upi;
}
double StatisticalAnalysis::getLpi(){
    return lpi;
}

//Recibe una linea del archivo como string
//Se encarga de crear la tupla y meterla en
//el vector de tuplas
//.i
void StatisticalAnalysis::setTuple(string sLine){
    Tuple currLine;
    string x = "";
    int pos = sLine.find(",");
    x = sLine.substr(0,pos);
    string y = sLine.substr(pos+1);
    if(y.find(",") != -1){
        cout << "Los elementos del archivo no se encuentran en el formato requerido" << endl;
        exit(1);
    } else {
        
        currLine.setX(stod(x));
        currLine.setY(stod(y));
        tuples.push_back(currLine);
    }
 
}

//Este metodo calcula y almacena el valor de b1
//.i
void StatisticalAnalysis::calcB1(){
    b1 = (sumXY - (n * avgX * avgY)) / (sumX2 - (n * pow(avgX,2.0)));
   
}

//Este metodo calcula y almancena el valor de r
//.i
void StatisticalAnalysis::calcRXY(){
    r = ((n * sumXY) - (sumX * sumY)) / sqrt((((n * sumX2) - pow(sumX,2.0)) * ((n * sumY2) - pow(sumY,2.0))));
}

//Este metodo calcula y almacena el valor de r2
//.i
void StatisticalAnalysis::calcR2(){
    r2 = pow(r ,2.0);
}

//Este metodo calcula y almacena el valor de b0
//.i
void StatisticalAnalysis::calcB0(){
    b0 = avgY - b1 * avgX;
}

//Este metodo calcula y almacena el valor de yk
//.i
void StatisticalAnalysis::calcYk(){
    yk = b0 + b1 * xk;
}

//Este metodo se encarga de realizar todos los calculos necesarios
//del documento de requerimientos 
//.i
void StatisticalAnalysis::calcTuples(){
    double sumYBX = 0;
    double sumXdif = 0;
    double newX = 0;
    Significance instSig; //Significance object instance
    Interval instInt; //Interval object instance 
    n = tuples.size();
    for(int i=0; i < tuples.size(); i++){ 
        sumX += tuples[i].getX();
        sumY += tuples[i].getY();
        sumX2 += pow(tuples[i].getX(),2.0);
        sumY2 += tuples[i].getY() * tuples[i].getY();
        sumXY += tuples[i].getX() * tuples[i].getY();
        
    }
   
    avgX = sumX / n;
    avgY = sumY / n;
    calcB1();
    calcRXY();
    calcR2();
    calcB0();
    calcYk();
    sig = instSig.calcSignificance(r,n,r2);

    //Calculate sumYBX && sumXdif for prediction Calculations
    for (int i=0; i < tuples.size(); i++){
        sumYBX += pow(tuples[i].getY() - b0 -(b1 * tuples[i].getX()),2);
        sumXdif += pow(tuples[i].getX() - avgX,2);
    }

    //Find value of x with 0.35 probability 
    CalculateX instCalcX(0.35, n -2);
    newX = instCalcX.findX();
    range = instInt.calcRange(newX,n,xk,avgX,sumYBX,sumXdif);
    upi = yk + range;
    lpi = yk - range > 0 ? yk - range : 0;
    
}