#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "StatisticalAnalysis.h"
using namespace std;
//.b=185
class ReadFile{
    //.d=6
    private:
    void openFile(string);
    void printResults(StatisticalAnalysis);
    string removeWhiteSpaces(string);

    public:
    ReadFile(string);



};

//Constructor
ReadFile::ReadFile(string fileName){
    openFile(fileName);
}

//.d=69
string ReadFile::removeWhiteSpaces(string str){
    string clean = "";
    for (int i=0; i < str.length(); i++){
        if (str[i] != ' ' && str[i] != '\t'){
            clean += str[i];
        }
    }
    return clean;
}

//.i
void ReadFile::printResults(StatisticalAnalysis currFile){
    cout << " N = "  << currFile.getN() << endl;
    cout << " xk = " << currFile.getXk() << endl;
    cout << fixed;
    cout << setprecision(5) << " r = "  << currFile.getR() << endl;
    cout << setprecision(5) << " r2 = " << currFile.getR2() << endl;
    cout << setprecision(5) << " b0 = " << currFile.getB0() << endl;
    cout << setprecision(5) << " b1 = " << currFile.getB1() << endl;
    cout << setprecision(5) << " yk = " << currFile.getYk() << endl;
}
//.i
void ReadFile::openFile(string fileName){
    ifstream myInputFile;
    myInputFile.open(fileName.data()); //.m

    //Check if the file exists
     if (!myInputFile){
            cout << "Imposible abrir el archivo " << "'" + fileName + "'" + " para lectura" <<endl;
             return;
        }

     //Check if the file is empty
     if (myInputFile.peek() == ifstream::traits_type::eof()){
         cout << "El archivo esta vacio" << endl;
        return;
     }

     if(myInputFile){
         //.d=78
         StatisticalAnalysis currFile;
         
         string sLine;
         getline(myInputFile, sLine);
        currFile.setXk(stoi(sLine));


         while (!myInputFile.eof()){
             getline(myInputFile, sLine);
             sLine = removeWhiteSpaces(sLine);
             currFile.setTuple(sLine);         
        }

        //Make calculations
        currFile.calcTuples();
        printResults(currFile);

        
      
     }

     //Close file
     myInputFile.close();

}