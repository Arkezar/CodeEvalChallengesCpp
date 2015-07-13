#include <iostream>
#include <fstream>
using namespace std;

bool convert( char& c, bool& upper){
    if(!upper) {
        if (c <= 'Z' && c >= 'A') {
            c = c - ('Z' - 'z');
            return true;
        } else if(c <= 'z' && c >= 'a'){
            return true;
        }
    } else {
        if (upper && c <= 'z' && c >= 'a') {
            c = c + ('Z' - 'z');
            return true;
        } else if (c <= 'Z' && c >= 'A'){
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);

    string line;
    bool up;
    while (getline(stream, line)) {
        up = true;

        for(int i = 0; i < line.size(); i++){
            bool tmp = convert(line[i],up);
            if(tmp)
                up = !up;

        }
        std::cout << line << std::endl;
    }
    return 0;
}