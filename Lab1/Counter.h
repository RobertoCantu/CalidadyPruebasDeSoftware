#include <iostream>
using namespace std;

class Counter {
    private:
        int whiteLines;
        int commentLines;
        int codeLines;

    public:
        Counter();
        void addWhiteLine();
        void addCommentLine();
        void addCodeLine();
        int getWhiteLines();
        int getCommentLines();
        int getCodeLines();
}

//Constructor 
Counter::Counter(){

    whiteLines = 0;
    commentLines = 0;
    codeLines = 0;
}

//Methods implementation
void Counter::addWhiteLine(){
    this->whiteLines += 1;
}

void Counter::addCommentLine(){
    this->commentLines += 1;
}

void Counter::addCodeLine(){
    this->codeLines += 1;
}

int Counter::getWhiteLines(){
    return whiteLines;
}

int Counter::getCommentLines(){
    return commentLines;
}

int Counter::getCodeLines(){
    return codeLines;
}
