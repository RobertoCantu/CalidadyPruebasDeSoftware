#include <iostream>
#include "Counter.h"
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

class ReadFile {
    private:
        Counter lineCounter;
        string removeWhiteSpeces(string str);
        void openFile(string fileName);

    public:
    ReadFile(string fileName);
        
}

//Methods implementation

ReadFile::ReadFile(string fileName){
    openFile(fileName);
}

string ReadFile::removeWhiteSpeces(string str){
    string clean = "";
    for (int i=0; i < str.length(); i++){
        if (str[i] != ' ' || str[i] != '\t'){
            clean += str[i];
        }
    }

    return clean;


}

void ReadFile::openFile(string fileName){
    ifstream myInputFile;
    myInputFile.open(fileName.data());

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
        bool comment = false;
        string sLine;
        while (!myInputFile.eof()){
            getline(myInputFile, sLine);
            sLine = removeWhiteSpeces(sLine);

            if (comment){
                if (sLine.find("/*") != string::npos){
                    comment = false;
                    lineCounter.addCommentLine();
                } else {
                    lineCounter.addCommentLine();
                }

            } else {
                if (sLine.find("//") != string::npos){
                    lineCounter.addCommentLine();
                }
                
                else if(sLine.find("/*") != string::npos){
                    lineCounter.addCommentLine();
                    comment = true;
                }
                else if (sLine.length() == 0){
                    lineCounter.addWhiteLine();
                } else {
                    lineCounter.addCodeLine();
                }
            }
        }
        cout << "Nombre del archivo: " << fileName << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Cantidad de lineas en blanco: " << lineCounter.getWhiteLines << endl;
        cout << "Cantidad de lineas con comentarios: " << lineCounter.getcommentLines() << endl;
        cout << "Cantiad de lineas con codigo: " << lineCounter.getcodeLines() << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Cantidad total de lineas: " << lineCounter.getwhiteLines() + lineCounter.getcommentLines() + lineCounter.getcodeLines() << endl;
    }


}