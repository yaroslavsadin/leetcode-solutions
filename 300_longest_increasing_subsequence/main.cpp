#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <optional>

class Solution {
public:
    template<typename It>
    int Recurse(It first, It last, int current) {
        auto idx = std::distance(first,last);
        if(dp[idx].has_value()) {
            return *dp[idx];
        }
        if(first == last) {
            return 0;
        }
        int lis = 0;
        for(; first != last; first++) {
            if(*first > current) {
                lis = std::max(lis,1 + Recurse(next(first), last, *first));
            }
        }
        dp[idx] = lis;
#ifdef DEBUG
        std::cerr << "Current: " << current << ", LIS: " << lis << std::endl;
#endif
        return lis;
    }
    
    int lengthOfLIS(std::vector<int>& nums) {
        if(nums.empty()) {
            return 0;
        }
        int res = 0;
        dp.resize(nums.size() + 1);
        for(auto it = nums.begin(); it != nums.end(); it++) {
#ifdef DEBUG
            std::cerr << "Starting at " << *it << ":\n";
#endif
            res = std::max(res,1 + Recurse(it,nums.end(),*it));
#ifdef DEBUG
            std::cerr << std::endl;
#endif
        }
        return res;
    }
private:
    std::vector<std::optional<int>> dp;
};

int main(void) {
    // std::vector<int> input = {3, 10, 2, 1, 20};
    std::vector<int> input = {1,3,6,7,9,4,10,5,6};
    std::cout << Solution().lengthOfLIS(input) << std::endl;
    return 0;
}