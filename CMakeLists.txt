cmake_minimum_required(VERSION 3.2)
project(Challanges)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(Primes primes.cpp)
add_executable(Rollercoster rollercoster.cpp)
add_executable(SumOfDigits sumofdigits.cpp)
add_executable(FizzBuzz FizzBuzz.cpp)
add_executable(PrimePal primepalindrome.cpp)
add_executable(ReverseWords reversewords.cpp)