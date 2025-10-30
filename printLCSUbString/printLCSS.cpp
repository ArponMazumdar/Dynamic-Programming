#include <iostream>
#include <vector>
#include <string>

std :: string longestCommonSubString(std :: vector <std :: vector<std :: vector <std :: string>>> &dp, std :: string &s1, std :: string &s2, std :: string s = "", int i = 0, int j = 0){
    if(i == s1.size() || j == s2.size()){
        return "";
    }
    
}