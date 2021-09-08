#include <iostream>
#include <string>
#include <vector>
#include "ReadFile.h"

using namespace std;

int main(){
    string file;
    cin >> file;
    ReadFile obj(file);
    return 0;
};