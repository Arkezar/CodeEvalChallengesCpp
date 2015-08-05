//
// Created by arkezar on 26.07.15.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);
//    ifstream stream("/home/arkezar/flavius");
    string line;
    string token;
    vector<int> nums;
    vector<int> people;
    vector<int> executedOrder;
    int n, m;
    while (getline(stream, line)) {
        istringstream ss(line);
        while(getline(ss,token,',')){
            nums.push_back(stoi(token));
        }

        n = nums[0];
        m = nums[1];

        for(int i = 0; i < n; i++){
            people.push_back(i);
        }

//        for(auto a : people){
//            cout << a << endl;
//        }

        int counter = 0;
        int cur = 0;

        while(executedOrder.size() != n) {
            counter++;
            if(counter % m == 0){
                counter = 0;
                executedOrder.push_back(people[cur]);
            }
            cur++;

            if(cur % people.size() == 0) {
                cur = 0;

                for (const auto &e : executedOrder) {
                    auto it = find(people.begin(), people.end(), e);
                    if (it != people.end())
                        people.erase(it);
                }

            }
        }

        nums.clear();
        people.clear();

        for(const auto& e : executedOrder){
            cout << e << " ";
        }
        cout << endl;
        executedOrder.clear();
    }
    return 0;
}