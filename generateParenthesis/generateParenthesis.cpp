#include <iostream>
#include <vector>
#include <string>

std :: vector < std :: string > GenerateParenthesis(int &n, int i = 0, int j = 0){
    if(i == n && j == n){
        return {""};
    }

    std :: vector < std :: string > ans;
    if(i < n){
        for(std :: string row : GenerateParenthesis(n, i + 1, j)){
            ans.push_back("(" + row);
        }
    }

    if(j < n){
        for(std :: string row : GenerateParenthesis(n, i, j + 1)){
            ans.push_back(")" + row);
        }
    }

    return ans;
}

int main(){
    int n = 2;
    std :: vector < std :: string > ans = GenerateParenthesis(n);
    for(std :: string parenthesisCombination : ans){
        std :: cout << parenthesisCombination << std :: endl;
    }
    return 0;
}