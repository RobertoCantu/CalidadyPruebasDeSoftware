#include <math.h>
#include <stdlib.h> 
#include <iostream>

//# define PI 3.14159265358979323846
#define _USE_MATH_DEFINES
//.b=60
class StatisticalAnalysis{
    private:
        double numSeg; //Must be an even number
        double acceptableError; //Maximum error
        double oldResult;
        double newResult;
        double gamma( double);
        double tDistribution( double, int);
        bool firstTime = false;
    


    public:
        StatisticalAnalysis(); //Constructor 
        double simpsonsRule( double,int);

};

StatisticalAnalysis::StatisticalAnalysis(){ 
    numSeg = 100;
    acceptableError = 0.00000001 ;
    oldResult = 0.0;
    newResult = 0.0;
}

//.i
 double StatisticalAnalysis::gamma(double num){
    if(num == 1){
        return 1.0;
    }
    else if(num == 0.5){
        return sqrt(M_PI);
    } else {
        return (num-1.0)*gamma(num - 1.0);
    }

}

//.i
 double StatisticalAnalysis::tDistribution( double x, int dof){
    return (gamma((dof+1.0) / 2.0) / (pow((dof * M_PI),0.5) * gamma(dof/2.0))) * pow((1.0 + (x*x /dof)),-(dof+1.0) / 2.0 );
}

//.i
 double StatisticalAnalysis::simpsonsRule( double x, int dof){
    int i = 1;
    double w = x / numSeg;
    double sumImpair = 0.0;
    double sumPair = 0.0;
    double tempResult = 0.0;

    for (i; i < numSeg; i++){
        if (i % 2 == 0){
            sumPair += tDistribution( i * w, dof);
        } else {
            sumImpair += tDistribution(i * w, dof);
        }
    }
    
    tempResult = (tDistribution(0.0,dof) + 4.0 * sumImpair + 2.0 * sumPair + tDistribution(i*w,dof)) * w / 3.0;
   
   //Conditionals for loading first results 
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

    else if (oldResult == 0 && newResult == 0){
        oldResult = tempResult;
        numSeg *= 2;
        return simpsonsRule(x,dof);
    }

    else if (oldResult > 0 && newResult == 0){
        newResult = tempResult;
        numSeg *= 2;
        return simpsonsRule(x,dof);
    }
}