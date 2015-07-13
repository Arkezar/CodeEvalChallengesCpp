#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);

    string line;
    vector<string> split;
    vector<string> nums;
    int start;
    int x, y, n;
    while (getline(stream, line)){
        split.clear();
        start = 0;
        for(int i = 0; i < line.length(); i++){
            if(line[i] == ' ' || i == line.length()-1){
                split.push_back(line.substr(start,i));
                start = i+1;
            }
        }

        x = stoi(split[0]);
        y = stoi(split[1]);
        n = stoi(split[2]);

        nums.clear();
        for(int i = 1; i <= n; i++){
            if(i % x == 0 && i % y ==0){
                nums.push_back("FB");
            }else if(i % y == 0){
                nums.push_back("B");
            }else if(i % x == 0){
                nums.push_back("F");
            }else{
                nums.push_back(to_string(i));
            }

        }

        for(auto s : nums){
            std::cout << s << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
