//
// Created by arkezar on 15.07.15.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>

using namespace std;

int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);
//    ifstream stream("/home/arkezar/binary");

    string line;
    string token;

    vector<int> nums;

    string bin;

    while (getline(stream, line)) {
        istringstream ss(line);
        while (getline(ss, token, ',')) {
            nums.push_back(stoi(token));
        }

        bin = bitset<64>(nums[0]).to_string();

        if(bin[bin.length()-nums[1]]==bin[bin.length()-nums[2]]){
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
        nums.clear();
    }

    return 0;
}