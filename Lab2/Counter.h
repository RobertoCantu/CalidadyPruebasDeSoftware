#include <iostream>
#include <string>
using namespace std;
//.b=31
class Counter {
    private:
    //.d=2
        string fileName;
        char classType;
        int codeLines;
        int itemLines;
        int baseLines;
        int deletedLines;
        int modifiedLines;
        int addedLines;



    public:
    //.d=2
    Counter();
    void setFileName(string);
    void setClassType(char);
    void addCodeLine();
    void addItemLine();
    void setBaseLines(int);
    void setDeletedLines(int);
    void addModifiedLine();
    void setAddedLines(int);
    string getFileName();
    char getClassType();
    int getCodeLines();
    int getItemLines();
    int getBaseLines();
    int getDeletedLines();
    int getModifiedLines();
    int getAddedLines();


};

//Constructor 
Counter::Counter (){
    //.d=2
    fileName = "";
    classType = '0';
    codeLines = 0;
    itemLines = 0;
    baseLines = 0;
    deletedLines = 0;
    modifiedLines = 0;
    addedLines = 0;
}

//Method Declaration
//.d=4
void Counter::setFileName(string fileName){
    this->fileName = fileName;
}

void Counter::setClassType(char classType){
    this->classType = classType;
}

void Counter::addCodeLine(){
    this->codeLines += 1;
}

void Counter::addItemLine(){
    this->itemLines += 1;
}

void Counter::setBaseLines(int baseLines){
    this->baseLines += baseLines;
}

void Counter::setDeletedLines(int deletedLines){
    this->deletedLines += deletedLines;
}

void Counter::addModifiedLine(){
    this->modifiedLines += 1;
}
void Counter::setAddedLines(int addedLines){
    this->addedLines += addedLines;
}
string Counter::getFileName(){
    return fileName;
}
char Counter::getClassType(){
    return classType;
}
int Counter::getCodeLines(){
    return codeLines;
}
int Counter::getItemLines(){
    return itemLines;
}
int Counter::getBaseLines(){
    return baseLines;
}
int Counter::getDeletedLines(){
    return deletedLines;
}
int Counter::getModifiedLines(){
    return modifiedLines;
}
int Counter::getAddedLines(){
    return addedLines;
}
