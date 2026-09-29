#include <iostream>
#include <vector>
#include <string>

std :: vector < std :: string > GenerateParenthesis(int &n, int i = 0, int j = 0){
    if(i == n && j == n) return {""};

    std :: vector <std :: string> ans = {};
    if(i < n){
        auto res = GenerateParenthesis(n, i + 1, j);
        for(auto s : res){
            ans.push_back("(" + s);
        }
    }
    if(i > 0 && j < i){
        auto res = GenerateParenthesis(n, i, j + 1);
        for(auto s : res){
            ans.push_back(")" + s);
        }
    }
    return ans;
}

int main(){
    int n = 4;
    std :: vector < std :: string > ans = GenerateParenthesis(n);
    for(std :: string parenthesisCombination : ans){
        std :: cout << parenthesisCombination << std :: endl;
    }
    return 0;
}