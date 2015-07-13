#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);

    string line;
    int sum;
    while (getline(stream, line)) {
        sum = 0;
        for(int i = 0; i < line.length(); i++){
            sum += line[i] - (int)'0';
        }
        std::cout << sum << std::endl;
    }
    return 0;
}