#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool isPalindrome(const string& pal){
    int length = pal.length();
    for(int i=0;i<length/2+1;i++){
        if(pal[i] != pal[length-i-1]){
            return false;
        }
    }

    return true;
}

int main(int argc, char *argv[]) {

    vector<bool> primes(1000,true);

    for(int i = 2; i<sqrt(primes.size());i++){
        if(primes[i] == true){
            for(int j = pow(i,2); j < primes.size(); j+=i){
                primes[j] = false;
            }
        }
    }

    for(int i = primes.size()-1; i >= 2; i--){
        if(primes[i]){
            if(isPalindrome(to_string(i))) {
                std::cout << i << std::endl;
                break;
            }
        }
    };
    return 0;
}