//
// Created by arkezar on 15.07.15.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

bool isInt(const double& num){
    return num == floor(num);
}

int modul(const double& n, const double& m){
    if(isInt(n/m)){
        return 0;
    } else {
        return n - floor(n/m)*m;
    }
}

int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);
//    ifstream stream("/home/arkezar/mod");
    string line;
    string token;
    vector<int> nums;
    while (getline(stream, line)) {
        istringstream ss(line);
        while(getline(ss,token,',')){
            nums.push_back(stoi(token));
        }

        cout << modul(nums[0],nums[1]) << endl;

        nums.clear();
    }

    return 0;
}