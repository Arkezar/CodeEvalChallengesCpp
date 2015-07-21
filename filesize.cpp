//
// Created by arkezar on 15.07.15.
//

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    ifstream stream(argv[1], ios::binary | ios::ate);
//    ifstream stream("/home/arkezar/permut", ios::binary | ios::ate);
    cout << stream.tellg() << endl;

    return 0;
}