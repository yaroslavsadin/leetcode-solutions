#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map<int,int> diffs;
        // Going through the array
        for(int i = 0; i < nums.size(); i++) {
            auto diff = target - nums[i];
            if(diffs.count(diff)) {
                // diffs.at(diff) + [i] = target
                return {i,diffs.at(diff)};
            } else{
                // Cache the difference between target and [i]
                diffs[nums[i]] = i;
            }
        }
        return {};
    }
};