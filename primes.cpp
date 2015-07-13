#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool isPrime(const int& num){
    if(num > 2)
        for(int i = 2; i < num; i++){
            if(num % i == 0)
                return false;
        }
    return true;
}

int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);
    string line;

    std::vector<int> primes;
    int number = 2;
    while (getline(stream, line)) {
    }

    while (primes.size() < 1000) {
        if (isPrime(number)) {
            primes.push_back(number);
        }
        number++;
    }

    long int sum = 0;
    for (int i = 0; i < primes.size(); i++) {
        sum += primes[i];
    }

    std::cout << sum;
    return 0;
}