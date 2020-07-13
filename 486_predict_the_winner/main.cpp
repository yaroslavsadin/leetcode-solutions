#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>

class Solution {
public:
    enum class Turn { PLAYER1, PLAYER2 };
    
    bool Recurse(const std::vector<int>& nums, int first, int last, int sum1, int sum2, Turn turn) {
#ifdef DEBUG
        std::cerr << first << ' ' << last << ' ' << static_cast<int>(turn) << std::endl;
#endif
        if(last == first) {
            if(turn == Turn::PLAYER1)  {
                return (sum1 + nums[first] > sum2);
            } else {
                return (sum1 > sum2 + nums[first]);
            }
        }
        if(turn == Turn::PLAYER1) {
            return !Recurse(nums,first+1,last,sum1+nums[first],sum2,Turn::PLAYER2)
            || !Recurse(nums,first,last-1,sum1+nums[last],sum2,Turn::PLAYER2);
        } else {
            return !Recurse(nums,first+1,last,sum1,sum2+nums[first],Turn::PLAYER1)
            || !Recurse(nums,first,last-1,sum1,sum2+nums[last],Turn::PLAYER1);
        }
    }
    
    bool PredictTheWinner(const std::vector<int>& nums) {
        if(nums.size() == 1) {
            return true;
        }
        return Recurse(nums,0,nums.size()-1,0,0,Turn::PLAYER1);
    }
};

int main(void) {
    std::cout << std::boolalpha << Solution().PredictTheWinner({306416,2889306,7742619,3897090,6904996,1954213,8815586,9031637,256723,4662300,3024674,5433146,8190137,5093129,9258336,3161122,3217503,1331124,9213976,8810715}) << std::endl;
    return 0;
}