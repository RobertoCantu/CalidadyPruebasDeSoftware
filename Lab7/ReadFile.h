//Autor: Roberto Cantu Reyes A01196704
//Fecha de creacion 21/08/2021
//Fecha de modificacion 05/11/2021
//Este es el archivo que se encarga de leer el archivo linea por linea
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "MultipleRegression.h"

using namespace std;
//.b=55
class ReadFile{
    private:
    void openFile(string);
    void printResults(MultipleRegression);
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
//.i
string ReadFile::removeWhiteSpaces(string str){
    string clean = "";
    for (int i=0; i < str.length(); i++){
        if (str[i] != ' ' && str[i] != '\t'){
            clean += str[i];
        }
    }
    return clean;
}

//Recibe un objeto con datos de tipo MultipleRegression
//Se encarga de imprimir los resultados en el formato especificado
//.i
void ReadFile::printResults(MultipleRegression currFile){
    cout << " N = "  << currFile.getN() << endl;
    cout << fixed;
    cout << setprecision(5) << " wk = " << currFile.getWk() << endl; //.m
    cout << setprecision(5) << " xk = "  << currFile.getXk() << endl; //.m
    cout << setprecision(5) << " yk = " << currFile.getYk() << endl; //.m
    cout << "------------" << endl;
    cout << setprecision(5) << " b0 = " << currFile.getB0() << endl; 
    cout << setprecision(5) << " b1 = " << currFile.getB1() << endl; 
    cout << setprecision(5) << " b2 = " << currFile.getB2() << endl; //.m
    cout << setprecision(5) << " b3 = " << currFile.getB3() << endl; //.m
    cout << "------------" << endl;
    cout << setprecision(5) << " zk = " << currFile.getZk() << endl; //.m
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
         MultipleRegression currFile;
         string sLine;
         //.d=2
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