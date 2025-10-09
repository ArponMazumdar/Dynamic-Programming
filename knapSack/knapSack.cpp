#include <iostream>
#include <vector>
#include <chrono>

int knapSack(std :: vector <int> &val, std :: vector <int> &wgt, std :: vector <std :: vector < int >> &dp, int weight, int &n, int i = 0){
    if(i >= n || weight == 0){
        return 0;
    }

    if(i == n - 1){
        return (wgt[i] <= weight) ? val[i] : 0;
    }

    int max_val = 0;
    for(int j = i; j < n; j++){
        if(wgt[j] <= weight){
            if(dp[j][weight] != -1){
                max_val = std :: max(max_val, dp[j][weight]);
                continue;
            }

            dp[j][weight] = val[j] + knapSack(val, wgt, dp, weight - wgt[j], n, j + 1);
            max_val = std :: max(max_val, dp[j][weight]);
        }        
    }
    return max_val;
}

int KnapSack(std :: vector <int> &val, std :: vector <int> &wgt, std :: vector <std :: vector < int >> &dp, int weight, int &n, int i = 0){
    if(i >= n || weight == 0){
        return 0;
    }

    if(i == n - 1){
        return (wgt[i] <= weight) ? val[i] : 0;
    }

    if(dp[i][weight] != -1){
        return dp[i][weight];
    }

    int curr_val = 0, max_val = 0;
    for(int j = i; j < n; j++){
        if(wgt[j] <= weight){
            curr_val = val[j] + KnapSack(val, wgt, dp, weight - wgt[j], n, j + 1);
            max_val = std :: max(max_val, curr_val);
        }        
    }
    return dp[i][weight] = max_val;
}

int knap_sack(std :: vector <int> &val, std :: vector <int> &wgt, std :: vector <std :: vector < int >> &dp, int weight, int &n, int i = 0){
    if(i >= n || weight == 0){
        return 0;
    }

    if(i == n - 1){
        return (wgt[n - 1] <= weight) ? val[n - 1] : 0;
    }

    if(dp[i][weight] != -1){
        return dp[i][weight];
    }

    int take = (wgt[i] <= weight) ? val[i] + knap_sack(val, wgt, dp, weight - wgt[i], n, i + 1) : 0;
    int skip = knap_sack(val, wgt, dp, weight, n, i + 1);

    return dp[i][weight] = std :: max(take, skip);
}

int knap_sack_T(std :: vector <int> &val, std :: vector <int> &wgt, int &weight){
    int n = val.size();
    std :: vector <int> dp(weight + 1, 0);
    std :: vector <int> curr = dp;
    
    for(int i = 1; i <= weight; i++){
        if(i >= wgt[n - 1]){
            dp[i] = val[n - 1];
        }
    }

    for(int i = n - 2; i >= 0; i--){
        for(int j = 1; j <= weight; j++){
            int take = (wgt[i] <= j) ? (val[i] + dp[j - wgt[i]]) : 0;
            int skip = dp[j];
            curr[j] = std :: max(take, skip);
        }
        dp = curr;
    }
    return dp[weight];
}

int main(){
    int maxWeight = 120;
    std :: vector <int> val = {4, 7, 9, 6, 2, 8, 11, 9, 14, 19, 21};
    std :: vector <int> wgt = {1, 3, 5, 4, 6, 9, 1, 7, 5, 9, 8};
    int n = val.size();
    std :: vector <std :: vector < int >> dp (n, std :: vector <int> (maxWeight + 1, -1));

    auto s = std :: chrono :: high_resolution_clock :: now();
    int ans = knapSack(val, wgt, dp, maxWeight, n);
    auto e = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <double> d = e - s;

    dp.assign(n, std :: vector <int> (maxWeight + 1, -1));
    auto s_1 = std :: chrono :: high_resolution_clock :: now();
    int ans_1 = KnapSack(val, wgt, dp, maxWeight, n);
    auto e_1 = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <double> d_1 = e_1 - s_1;

    dp.assign(n, std :: vector <int> (maxWeight + 1, -1));
    auto s_2 = std :: chrono :: high_resolution_clock :: now();
    int ans_2 = knap_sack(val, wgt, dp, maxWeight, n);
    auto e_2 = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <double> d_2 = e_2 - s_2;

    auto s_3 = std :: chrono :: high_resolution_clock :: now();
    int ans_3 = knap_sack_T(val, wgt, maxWeight);
    auto e_3 = std :: chrono :: high_resolution_clock :: now();
    std :: chrono :: duration <double> d_3 = e_3 - s_3;

    std :: cout <<"For maxWeight = " << maxWeight << std :: endl 
    << "result" << "      time " << std :: endl 
    << ans << "    |    " << d.count() << std :: endl
    << ans_1 << "    |    " << d_1.count() << std :: endl
    << ans_2 << "    |    " << d_2.count() << std :: endl
    << ans_3 << "    |    " << d_3.count() << std :: endl;
    return 0;
}