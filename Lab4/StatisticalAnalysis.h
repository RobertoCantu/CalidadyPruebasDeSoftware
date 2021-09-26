#include <iostream>
#include <math.h>
#include <stdlib.h> 

# define PI 3.14159265358979323846
class StatisticalAnalysis{
    private:
    int numSeg; //Must be an even number
    double acceptableError;
    double oldResult;
    double newResult;
    double gamma(double);
    double tDistribution(double, int);
    bool firstTime = false;
    


    public:
    StatisticalAnalysis(); //Constructor 
    double simpsonsRule(double,int);


};

StatisticalAnalysis::StatisticalAnalysis(){
    numSeg = 10;
    acceptableError = 0.0000001;
    oldResult = 0.0;
    newResult = 0.0;
}

double StatisticalAnalysis::gamma(double num){
    if(num == 1){
        return 1.0;
    }
    else if(num == 0.5){
        return sqrt(PI);
    } else {
        return (num-1.0)*gamma(num - 1.0);
    }

}

double StatisticalAnalysis::tDistribution(double x, int dof){
    return (gamma((dof+1.0) / 2.0) / (pow((dof * PI),0.5) * gamma(dof/2.0))) * pow((1.0 + (pow(x,2.0) / dof)),-(dof+1.0) / 2.0 );
}

double StatisticalAnalysis::simpsonsRule(double x, int dof){
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