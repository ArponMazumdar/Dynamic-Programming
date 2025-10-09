#include <iostream>
#include <vector>

int tribonacci(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    if(n == 2) return 1;
    
    std :: vector <int> trib(n + 1, 0);
    trib[1] = 1;
    trib[2] = trib[0] + trib[1];

    for(int i = 3; i <= n; i++){
        trib[i] = trib[i - 1] + trib[i - 2] + trib[i - 3];
    }

    return trib[n];
}

int main(){
    int n = 0;
    std :: cout << n << " th tribonacci = " << tribonacci(n) << std :: endl;
    return 0;
}