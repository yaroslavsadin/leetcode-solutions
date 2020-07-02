#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>
#include <cassert>
using namespace std;

class Solution {
private:
    std::vector<int> dp_array;
public:
    std::optional<int> DPRecursive(int n, int cnt) {
        if(n == 0) {
            return cnt;
        }
        std::optional<int> min_;
        for(int x = 1; x*x <= n; x++) {
            auto res = DPRecursive(n-x*x,cnt+1);
            if(res) {
                min_ = (min_) ? std::min(*min_,*res) : res;
            }
        }
        return *min_;
    }

    int DPtabulation(int n) {
        dp_array.resize(n + 1);
        for(int i = 1; i < dp_array.size(); i++) {
            dp_array[i] = dp_array[i-1] + 1;

            for(int j = 1; (j*j) <= i; j++) {
                dp_array[i] = std::min(dp_array[i],1 + dp_array[i-j*j]);
            }
        }
#ifdef DEBUG
        for(auto i : dp_array) {
            std::cerr << i << ' ';
        }
        std::cerr << std::endl;
#endif
        return dp_array.back();
    }
    
    int numSquares(int n) {
        return DPtabulation(n);
    }
};

int main(void) {
#ifdef ENABLE_STRESS_TEST
    for(int i = 2; i < 50; i++) {
        if(Solution().DPRecursive(i,0) != Solution().DPtabulation(i)) {
            std::cerr << "FAIL at: " << i << std::endl;
        }
    }
#endif
    std::cout << Solution().numSquares(15) << std::endl;
    return 0;
}
