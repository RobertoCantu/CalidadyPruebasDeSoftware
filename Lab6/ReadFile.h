//Autor: Roberto Cantu Reyes A01196704
//Fecha de creacion 21/08/2021
//Fecha de modificacion 15/09/2021
//Este es el archivo principal del programa 
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "StatisticalAnalysis.h"

using namespace std;
//.b=51
class ReadFile{
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

//Este metodo recibe un string como parametro
//Se encarga de remover los espacios en blanco que contenga el string 
//Regresa un string sin espacios en blanco
string ReadFile::removeWhiteSpaces(string str){
    string clean = "";
    for (int i=0; i < str.length(); i++){
        if (str[i] != ' ' && str[i] != '\t'){
            clean += str[i];
        }
    }
    return clean;
}

//Recibe un objeto con datos de tipo StatisticalAnalysis
//Se encarga de imprimir los resultados en el formato especificado
//.i
void ReadFile::printResults(StatisticalAnalysis currFile){
    cout << " N = "  << currFile.getN() << endl;
    cout << fixed;
    cout << setprecision(5) << " xk = " << currFile.getXk() << endl;
    cout << setprecision(5) << " r = "  << currFile.getR() << endl;
    cout << setprecision(5) << " r2 = " << currFile.getR2() << endl;
    cout << setprecision(5) << " b0 = " << currFile.getB0() << endl;
    cout << setprecision(5) << " b1 = " << currFile.getB1() << endl;
    cout << setprecision(5) << " yk = " << currFile.getYk() << endl;
    cout << setprecision(10) << " sig = " << currFile.getSig() << endl;
    cout << setprecision(5) << " ran = " << currFile.getRange() << endl;
    cout << setprecision(5) << " LS = " << currFile.getUpi() << endl;
    cout << setprecision(5) << " LI = " << currFile.getLpi() << endl;
}

//Recibe como parametro el nombre de un archivo
//Se encarga de hacer validar el archivo y de abrirlo para su lectura
//Al final cierra el archivo como buena practica  
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