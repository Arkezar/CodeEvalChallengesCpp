#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;
int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);

    string line;
    while (getline(stream, line)) {
        istringstream iss(line);
        vector<string> words{istream_iterator<string>{iss},istream_iterator<string>{}};

        for(int i = words.size()-1; i >= 0; i--){
            std::cout << words[i] << " ";
        }
        std::cout << endl;
    }
    return 0;
}