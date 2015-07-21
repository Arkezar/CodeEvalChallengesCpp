//
// Created by arkezar on 15.07.15.
//

#include <iostream>
#include <fstream>
using namespace std;

inline int genFibonacci(const int& num){
    if(num == 0){
        return 0;
    } else if(num == 1){
        return 1;
    } else {
        return genFibonacci(num-1)+genFibonacci(num-2);
    }
}

int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);
//    ifstream stream("/home/arkezar/fib");
    string line;
    int num;
    while (getline(stream, line)) {
        num = stoi(line);
        if(num >= 0){

            cout << genFibonacci(num) << endl;
        }
    }
    return 0;
}