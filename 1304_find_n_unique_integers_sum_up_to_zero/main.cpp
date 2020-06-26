#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> sumZero(int n) {
        if(n == 1) {
            return {0};
        }
        vector<int> res;
        res.reserve(n);
        for(int i = 1; n > 0; i++) {
            if(n == 1) {
                res.push_back(0);
                n--;
            } else {
                res.push_back(i);
                res.push_back(-i);
                n -= 2;
            }
        }
        return res;
    }
};

int main(void) {
    Solution sol;
    for(int i : sol.sumZero(3)) {
        std::cerr << i << ' ';
    }
    return 0;
}