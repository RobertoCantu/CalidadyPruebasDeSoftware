#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Counter.h"
using namespace std;

class ReadFile {
    private:
    void openFile(string);
    string removeExtension(string);
    string removeWhiteSpaces(string);
    vector<Counter> files;
    int totalLines = 0;
    vector<Counter> assignClassType(vector<Counter>);
    void printResults(vector<Counter>);
    int convertStrToInt(string);
    bool insideStr(string);
    bool isInsideString(string);

    public:
    ReadFile(string);
};

//Constructor
ReadFile::ReadFile(string fileName){
    openFile(fileName);
    
}
bool ReadFile::isInsideString(string str){
    bool quote = false;

    for (int i=0; i < str.length(); i++){
        if (str[i] == '"'){
            quote = true;
            continue;
        }
        if (str[i] == '/'){
            if(quote && str[i+1] == '/' && str[i+2] == '.' && str[i+3] == 'm'){
                //Indeed it is inside a string
                return true;
            }
        }
    }
    return false;
}

//Methods declarations
bool ReadFile::insideStr(string str){
    //There is a string
    if (str.find("\"") != string::npos){
        return true;
    } else {
        return false;
    }
}

int ReadFile::convertStrToInt(string str){
    int pos = str.find("=");
    string temp = str.substr(pos + 1);
    int intStr = stoi(temp);
    return intStr;

}

void ReadFile::printResults(vector<Counter> files){

    cout << "CLASES BASE:" << endl;
    for (int i=0; i < files.size(); i++){
       if(files[i].getClassType() == 'B'){
           cout << "\t" << files[i].getFileName();
           cout << ": T=" << files[i].getCodeLines();
           cout << ", I=" << files[i].getItemLines();
           cout << ", B=" << files[i].getBaseLines();
           cout << ", D=" << files[i].getDeletedLines();
           cout << ", M=" << files[i].getModifiedLines();
           cout << ", A=" << files[i].getAddedLines() << endl;
           totalLines += files[i].getCodeLines();
        } 
    }
    cout << "--------------------------------------------" << endl;

    cout << "CLASES NUEVAS:" <<endl;
    for (int i=0; i < files.size(); i++){
        if(files[i].getClassType() == 'N'){
            cout << "\t" << files[i].getFileName();
            cout << ": T=" << files[i].getCodeLines();
            cout << ", I=" << files[i].getItemLines() << endl;
            totalLines += files[i].getCodeLines();
        }

    }
    cout << "--------------------------------------------" << endl;

    cout << "CLASES REUSADAS:" << endl;
    for (int i=0; i < files.size(); i++){
        if(files[i].getClassType() == 'R')
        {
            cout << "\t" << files[i].getFileName();
            cout << ": T=" << files[i].getCodeLines();
            cout << ", I=" << files[i].getItemLines();
            cout << ", B=" << files[i].getBaseLines() << endl;
            totalLines += files[i].getCodeLines();
        }
    }
    cout << "--------------------------------------------" << endl;

    cout << "Total de LDC=" << totalLines << endl;
}

vector<Counter> ReadFile::assignClassType(vector<Counter> files){
    for (int i=0; i < files.size(); i++){
        if(files[i].getBaseLines() > 0 && (files[i].getModifiedLines() > 0 || files[i].getDeletedLines() > 0 || files[i].getAddedLines() > 0)){
            files[i].setClassType('B');
        }
        else if(files[i].getBaseLines() == 0 && files[i].getModifiedLines() == 0 && files[i].getDeletedLines() == 0 && files[i].getAddedLines() > 0){
            files[i].setClassType('N');
        }
        else if(files[i].getBaseLines() > 0 && files[i].getModifiedLines() == 0 && files[i].getDeletedLines() == 0 && files[i].getAddedLines() == 0){
            files[i].setClassType('R');
         } 
    }
    return files;  

}
string ReadFile::removeExtension(string str){
    int pos = str.find(".");
    str = str.substr(0,pos);
    return str;
}

string ReadFile::removeWhiteSpaces(string str){
    string clean = "";
    for (int i=0; i < str.length(); i++){
        if (str[i] != ' ' && str[i] != '\t'){
            clean += str[i];
        }
    }
    return clean;
}

void ReadFile::openFile(string fileName){
     ifstream myInputFile;
     myInputFile.open(fileName.data());
     string newFileName = "";

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
         Counter currFile;
         bool comment = false;
         fileName = removeExtension(fileName);
         currFile.setFileName(fileName);
         string sLine;

         //Check if the fileName already exist in our vector
         for (int i=0; i < files.size(); i++){
             if(files[i].getFileName() == fileName){
                 currFile = files[i];
                 files.erase(files.begin() + i);
             }
         }

         while (!myInputFile.eof()){
             getline(myInputFile, sLine);
             sLine = removeWhiteSpaces(sLine);

             if (comment){
                 if (sLine.find("*/") != string::npos){
                     comment = false;
                     continue;
                     //Dont add line delete
                 } else {
                     continue;
                 }

            } else {
                if (sLine.find("/*") != string::npos){
                    //Dont add line delete
                    comment = true;
                    continue;
                }
                if (sLine.find("//") != string::npos){
                    //Dont add comment delete
                    //Check if it is an item
                    if(sLine.find("//.i") != string::npos){
                        //do something
                        currFile.addItemLine();
                        continue;
                    }
                    else if(sLine.find("//.b") != string::npos){
                        int baseLines = convertStrToInt(sLine);

                        currFile.setBaseLines(baseLines);
                        continue;
                        //We need a convert from string to int

                    }
                    else if(sLine.find("//.d") != string::npos){
                        //We need a convert from string to int
                        int deletedLines = convertStrToInt(sLine);
                        currFile.setDeletedLines(deletedLines);
                        continue;
                    }
                    else if(sLine.find("//.m") !=string::npos){
                        int pos = sLine.find("//");
                        if (pos == 0){
                            //Do nothing it is a comment
                            continue;
                            
                        } else {
                            //Check if it is not inside an string 
                            if(!isInsideString(sLine)){
                                currFile.addCodeLine();
                                currFile.addModifiedLine();
                            } else {
                                currFile.addCodeLine();
                            }         
                        }
                    } else {
                        int pos = sLine.find("//");
                        //This is probably a website
                        if (pos > 0){
                            currFile.addCodeLine();
                        }
                        
                    }
                 } else{
                    if (sLine.length() > 0 && sLine.length() <=2){
                        //Muy probablemente tengamos que ignorar esa linea
                    }
                    else if(sLine.length() == 0){
                        //Do nothing is an empty line
                    } else{
                        
                        currFile.addCodeLine();
                    }
                }
            }
        }

        //Asign new file to vector of Counters
        files.push_back(currFile);

        //Close File
        myInputFile.close();

        cout << "Enter new fileName or type 1 to end the program" << endl;
        cin >> newFileName;
        if (newFileName.length() == 1){
            //Added Lines
            for (int i=0; i < files.size(); i++){
                files[i].setAddedLines(files[i].getCodeLines() - files[i].getBaseLines() + files[i].getDeletedLines());
            }
            //After finishing program Assign Class Type && AddedLines 
            files = assignClassType(files);
            //Print results 
            printResults(files);
            return;
        } else {
            openFile(newFileName);
        }
     }
}