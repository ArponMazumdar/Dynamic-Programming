#include <iostream>
#include <vector>
#include <unordered_map>

class cell{
public:
    bool hasCalculated = false;
    std :: vector <std :: vector <int>> ans;
};

std :: vector <std :: vector <int>> CombinationSum(std :: vector <std :: vector <cell>> &dp, std :: vector <int> &candidates, int target, int depth = 0){
    if(target == 0) return {{}};
    if(depth == candidates.size()) return {};
    if(dp[depth][target].hasCalculated){
        return dp[depth][target].ans;
    }

    std :: vector <std :: vector <int>> res;
    for(int i = depth; i < candidates.size(); i++){
        if(candidates[i] <= target){
            for(auto &j : CombinationSum(dp, candidates, target - candidates[i], i)){
                j.push_back(candidates[i]);
                res.push_back(j);
            }
        }
    }
    dp[depth][target].hasCalculated = true;
    dp[depth][target].ans = res;
    return res;
}

std :: vector <std :: vector <int>> combinationSum(std :: vector <std :: vector <cell>> &dp, std :: vector <int> &candidates, int target, int depth = 0){
    if(target == 0) return {{}};
    if(depth == candidates.size()) return {};
    if(dp[depth][target].hasCalculated){
        return dp[depth][target].ans;
    }

    std :: vector <std :: vector <int>> ans;
    if(target >= candidates[depth]){
        for(auto &i : combinationSum(dp, candidates, target - candidates[depth], depth)){
            i.push_back(candidates[depth]);
            ans.push_back(i);
        }
    }
    auto i = combinationSum(dp, candidates, target, depth + 1);
    ans.insert(ans.end(), std :: make_move_iterator(i.begin()), std :: make_move_iterator(i.end()));
    dp[depth][target].hasCalculated = true;
    dp[depth][target].ans = ans;
    return ans;
}

void print(std :: vector <std :: vector <int>> &vec){
    for(auto &i : vec){
        for(auto &j : i){
            std :: cout << j << " ";
        }
        std :: cout << "\n";
    }
}

int main(){
    std :: vector <int> candidates = {1, 2, 3, 5};
    int target = 7;
    int n = candidates.size();
    std :: vector <std :: vector <cell>> dp(n, std :: vector<cell>(target + 1));
    std :: vector <std :: vector <int>> ans = CombinationSum(dp, candidates, target);
    print(ans);
    dp.assign(n, std :: vector <cell>(target + 1));
    auto ans1 = combinationSum(dp, candidates, target);
    print(ans1);
    return 0;
}