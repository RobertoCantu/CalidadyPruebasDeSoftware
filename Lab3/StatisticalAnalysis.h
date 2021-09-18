#include <vector>
#include "Tuple.h"
#include <string>
#include <math.h>
using namespace std;

class StatisticalAnalysis {
    private:
     double n;
     double xk;
     double r;
     double r2;
     double b0;
     double b1;
     double yk;
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



//Methods declarations
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
//.i
void StatisticalAnalysis::calcB1(){
    b1 = (sumXY - (n * avgX * avgY)) / (sumX2 - (n * pow(avgX,2.0)));
   
}
//.i
void StatisticalAnalysis::calcRXY(){
    r = ((n * sumXY) - (sumX * sumY)) / sqrt((((n * sumX2) - pow(sumX,2.0)) * ((n * sumY2) - pow(sumY,2.0))));
}
//.i
void StatisticalAnalysis::calcR2(){
    r2 = pow(r ,2.0);
}
//.i
void StatisticalAnalysis::calcB0(){
    b0 = avgY - b1 * avgX;
}
//.i
void StatisticalAnalysis::calcYk(){
    yk = b0 + b1 * xk;
}


//.i
void StatisticalAnalysis::calcTuples(){
    n = tuples.size();
    for(int i=0; i < tuples.size(); i++){ //Posible fix
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
}