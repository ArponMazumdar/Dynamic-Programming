#include <iostream>
#include <vector>
#include <chrono>
#include <climits>
#include <random>

std::vector<int> generatePriceArray(int n) {
    std::vector<int> price(n);
    std::mt19937 rng(87); 
    for (int i = 0; i < n; ++i) {
        price[i] = (i + 1) + (rng() % 3);
    }
    return price;
}

int max_price(std :: vector <int> &price, std :: vector <int> &dp, int length, int &n){
    if(length == 0){
        return 0;
    }

    if(length == 1){
        return price[0];
    }

    if(dp[length] != -1){
        return dp[length];
    }

    int curr_val = 0;
    int max_val = -1e9;
    for(int j = 1; j <= n; j++){
        if(j <= length){
            curr_val = price[j - 1] + max_price(price, dp, length - j, n);
        }
        max_val = std :: max(curr_val, max_val);
    }

    return dp[length] = max_val;
}

int maxPrice(std :: vector <int> &price, std :: vector <int> &dp, int length){
    if(length == 0){
        return 0;
    }

    if(length == 1){
        return price[0];
    }

    if(dp[length] != -1){
        return dp[length];
    }

    int curr_price = 0;
    int curr_max = 0;

    for(int j = 1; j <= length; j++){
        curr_price = price[j - 1] + maxPrice(price, dp, length - j);
        curr_max = std :: max(curr_max, curr_price);
    }

    return dp[length] = curr_max;
}

int max_Price(std :: vector <int> &price, std :: vector <std :: vector <int>> &dp, int &n, int length, int i = 0){
    if(length == 0 || i >= length){
        return 0;
    }

    if(i == n - 1){
        return (length <= n) ? price[n - 1] : 0;
    }

    if(dp[i][length] != -1){
        return dp[i][length];
    }

    int take = (i <= length - 1) ? price[i] + max_Price(price, dp, n, length - i - 1, i) : INT_MIN;
    int skip = max_Price(price, dp, n, length, i + 1);
    
    return dp[i][length] = std :: max(take, skip);
}

int Max_Price(std :: vector <int> &price, std :: vector <std :: vector <int>> &dp, int length, int i){
    if(length == 0){
        return 0;
    }

    if(i == 0){
        return dp[i][length] = (length * price[0]);
    }

    if(dp[i][length] != -1){
        return dp[i][length];
    }

    int take = (i <= length - 1) ? price[i] + Max_Price(price, dp, length - i - 1, i) : INT_MIN;
    int skip = Max_Price(price, dp, length, i - 1);
    
    return dp[i][length] = std :: max(take, skip);
}

int Max_Price_T(std :: vector <int> &price){
    int n = price.size();
    std :: vector <std :: vector <int>> dp(n, std :: vector <int>(n + 1, 0));

    for(int i = 1; i <= n; i++){
        dp[0][i] = price[0] * i;
    }

    for(int i = 1; i < n; i++){
        int rodLength = i + 1;
        for(int j = 1; j <= n; j++){
            int take = (j >= rodLength) ? price[i] + dp[i][j - rodLength] : 0;
            int skip = dp[i - 1][j];
            dp[i][j] = std :: max(take, skip);
        }
    }
    return dp[n - 1][n];
}

int maxPrice_T(std :: vector <int> &prices){
    int n = prices.size();
    std :: vector <int> dp(n + 1, 0);
    dp[1] = prices[0];

    for(int i = 2; i <= n; i++){
        int curr_sum = 0, max_sum = 0;
        for(int j = 1; j <= i; j++){
            curr_sum = prices[j - 1] + dp[i - j];
            max_sum = std :: max(curr_sum, max_sum);
        }
        dp[i] = max_sum;
    }
    return dp[n];
}

int main(){
    int len = 6176;
    std :: vector <int> price = generatePriceArray(len); 
    std :: vector <int> memo(len + 1, -1);

    auto s = std :: chrono :: high_resolution_clock :: now();
    int ans = max_price(price, memo, len, len);
    auto e = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <double> d = e - s;

    memo.assign(len + 1, -1);
    auto s_1 = std :: chrono :: high_resolution_clock :: now();
    int ans_1 = maxPrice(price, memo, len);
    auto e_1 = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <double> d_1 = e_1 - s_1;

    std :: vector <std :: vector <int>>dp(len, std :: vector <int> (len + 1, -1));
    auto s_2 = std :: chrono :: high_resolution_clock :: now();
    int ans_2 = max_Price(price, dp, len, len);
    auto e_2 = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <double> d_2 = e_2 - s_2;

    dp.assign(len, std :: vector <int> (len + 1, -1));
    auto s_3 = std :: chrono :: high_resolution_clock :: now();
    int ans_3 = Max_Price(price, dp, len, len - 1);
    auto e_3 = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <double> d_3 = e_3 - s_3;

    auto s_4 = std :: chrono :: high_resolution_clock :: now();
    int ans_4 = Max_Price_T(price);
    auto e_4 = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <double> d_4 = e_4 - s_4;

    auto s_5 = std :: chrono :: high_resolution_clock :: now();
    int ans_5 = maxPrice_T(price);
    auto e_5 = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <double> d_5 = e_5 - s_5;

    std :: cout <<"for rod length = " << len << std :: endl
    << ans << " | " << d.count() << std :: endl
    << ans_1 << " | " << d_1.count() << std :: endl
    << ans_2 << " | " << d_2.count() << std :: endl
    << ans_3 << " | " << d_3.count() << std :: endl
    << ans_4 << " | " << d_4.count() << std :: endl
    << ans_5 << " | " << d_5.count() << std :: endl;
    return 0;
}