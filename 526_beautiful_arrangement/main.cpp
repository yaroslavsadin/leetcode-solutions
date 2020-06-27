#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

/// XXX: https://www.geeksforgeeks.org/backtracking-introduction/
class Solution {
public:
    void countArrangementRecurse(int idx, int N) {
        if(idx == N + 1) {
            cnt++;
            return;
        }
        for(int num = 1; num <= N; num++) {
            if(!considered[num] && (num % idx == 0 || idx % num == 0)) {
                considered[num] = true;
                countArrangementRecurse(idx + 1, N);
                considered[num] = false;
            }
        }
    }

    int countArrangement(int N) {
        considered = std::vector<bool>(N+1);
        countArrangementRecurse(1,N);
        return cnt;
    }
private:
    std::vector<bool> considered;
    int cnt = 0;
};

int main(void) {
    std::cerr << Solution().countArrangement(4) << std::endl;
    return 0;
}