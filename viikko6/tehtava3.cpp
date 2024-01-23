#include <iostream>
#include "stack.h"

bool is_prime(int num) {
    if (num < 2) {
        return false;
    }
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void print_prime_divisors(int num) {
    Stack<int> primeDivisorsStack;
    for (int i = num / 2; i > 1; i--) {
        if (num % i == 0 && is_prime(i)) {
            primeDivisorsStack.push(i);
        }
    }
    Error_code err = success;
    while (true) {
        int divisor;
        err = primeDivisorsStack.top(divisor);
        err = primeDivisorsStack.pop();
        if (err != success) {
            break;
        }
        std::cout << divisor << " ";
    }
    std::cout << std::endl;
}

int main() {
    int input;
    std::cout << "Enter an integer: ";
    std::cin >> input;
    std::cout << "Prime divisors in descending order: ";
    print_prime_divisors(input);
    return 0;
}

