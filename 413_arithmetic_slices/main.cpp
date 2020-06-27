#include <iostream>
#include <vector>
#include <unordered_map>

/// XXX: Recursion + dynamic programming optimization
class Solution {
public:
    int Recurse(std::vector<int>& A, size_t idx, int diff) {
        if(memo.count(idx)) {
            return memo.at(idx);
        }
#ifdef DEBUG
    std::cerr << "Index " << idx << ": ";
    for(size_t i = idx; i < A.size(); i++) {
        std::cerr << A[i] << ' ';
    }
    std::cerr << std::endl;
#endif
        if(idx == A.size()-1) {
            memo[idx] = static_cast<int>(A[idx] - A[idx-1] == diff);
            return memo.at(idx);
        }
        if(A[idx] - A[idx-1] == diff) {
            memo[idx] = 1 + Recurse(A,idx+1,diff);
            return memo.at(idx);
        }
        return 0;
    }

    int numberOfArithmeticSlices(std::vector<int>& A) {
        if(A.size() < 3) {
            return 0;
        }

        int cnt = 0;
        for(size_t i = 0; i < A.size()-2; i++) {
            cnt += Recurse(A,i+2,A[i+1] - A[i]);
        }
        return cnt;
    }
private:
    std::unordered_map<int,int> memo;
};

int main(void) {
    std::vector<int> input{1,3,5,7,9};
    std::cout << Solution().numberOfArithmeticSlices(input);
    return 0;
}