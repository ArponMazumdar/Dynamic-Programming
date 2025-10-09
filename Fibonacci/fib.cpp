#include <iostream>
#include <vector>

long long int fibonacci(int n , std :: vector <int> & memo){
    if(n == 0 || n == 1)
        return n;

    if(memo[n] != -1) 
        return memo[n];

    memo[n] = fibonacci(n - 1 , memo) + fibonacci(n - 2 , memo);

    return memo[n];
}

long long int fibonacciTabulation(int n){
    std :: vector <int> fib(n + 1, 0);
    fib[0] = 0;
    fib[1] = 1;

    for(int i = 2; i <= n; i++){
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return fib[n];
}

int main(){
    int n = 40;
    std :: vector <int> dp(n + 1, -1);
    std :: cout << n << "th fibonacci = " << fibonacciTabulation(n) << std :: endl;
}