#include <iomanip>
#include <iostream>

using namespace std;

class PrintResults{
    private:
        double x;
        int dof;
        double probability;

    public:
    PrintResults(double,int,double); //Constructor 
    void print();


};

PrintResults::PrintResults(double x, int dof, double probability){
    this->x = x;
    this->dof = dof;
    this->probability = probability;
}

void PrintResults::print(){
    cout << fixed;
    cout << setprecision(5) << "x = " << x << endl;
    cout << "dof = " << dof << endl;
    cout << setprecision(5) << "p = " << probability << endl;

}