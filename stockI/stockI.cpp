#include <iostream>
#include <vector>

int maxProfit(std :: vector <int> &val){
    int maxProfit = 0;
    int currMin = val[0];
    for(int i = 1; i < val.size(); i++){
        maxProfit = std :: max(maxProfit, val[i] - currMin);
        currMin = std :: min(currMin, val[i]);
    }
    return maxProfit;
}

int main(){
    std :: vector <int> val = {1, 2, 8, 2, 6, 1, 4, 3, 9, 4, 2};
    int max_profit = maxProfit(val);
    std :: cout << "\nMax profit: " << max_profit << "\n";
    return 0;
}