//
// Created by arkezar on 15.07.15.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
//    ifstream stream(argv[1]);
    ifstream stream("/home/arkezar/fib");
    string line;
    vector<int> nums;
    while (getline(stream, line)) {
        nums.push_back(stoi(line));
    }
    int sum = 0;
    for(const auto& n : nums)
        sum += n;
    cout << sum << endl;
    return 0;
}