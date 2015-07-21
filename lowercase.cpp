//
// Created by arkezar on 15.07.15.
//

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);
//    ifstream stream("/home/arkezar/text");
    string line;

    while (getline(stream, line)) {
        for(int i = 0; i < line.size(); i++) {
            if (line[i] <= 'Z' && line[i] >= 'A') {
                line[i] = line[i] - ('Z' - 'z');
            }

        }
        std::cout << line << std::endl;
    }
    return 0;
}