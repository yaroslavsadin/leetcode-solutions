#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <optional>

class Solution {
public:
    int maxProduct(std::vector<int>& nums) {
        if(nums.size() == 0) {
            return 0;
        }
#if 0
        int max_ = *nums.begin();
        for(size_t i = 0; i < nums.size(); i++) {
            int acc = nums[i];
            max_ = std::max(acc,max_);
            for(int j = i + 1; j < nums.size(); j++) {
                acc *= nums[j];
                max_ = std::max(acc,max_);
            }
        }
        return max_;
#endif
        int min_prod = nums[0], max_prod = nums[0], res = nums[0];
        for(size_t i = 1; i < nums.size(); i++) {
            if(nums[i] < 0) {
                std::swap(min_prod,max_prod);
            }
            min_prod = std::min(min_prod*nums[i], nums[i]);
            max_prod = std::max(max_prod*nums[i], nums[i]);
            res = std::max(res,max_prod);
#ifdef DEBUG
            std::cerr << "min_prod: " << min_prod << ", max_prod: " << max_prod << std::endl;
#endif
        }
        return res;
    }
};

int main(void) {
    std::vector<int> nums = {3,-1,4};
    std::cout << Solution().maxProduct(nums) << std::endl;
}