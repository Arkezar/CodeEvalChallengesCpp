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

int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);
//    ifstream stream("/home/arkezar/nums");
    string line;
    string token;
    vector<int> nums;
    int x, n, multN;
    while (getline(stream, line)) {
        istringstream ss(line);
        while(getline(ss,token,',')){
            nums.push_back(stoi(token));
        }

        n = nums[1];
        x = nums[0];
        if(isInt(log2(n))) {
            multN = n;
            while (multN <= x) {
                multN += n;
            }

            cout << multN << endl;
        } else {
            cout << "Bad input" << endl;
        }
        nums.clear();
    }
    return 0;
}