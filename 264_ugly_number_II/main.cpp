#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <cassert>
using namespace std;

class Solution {
public:
    int find_next(const std::vector<int>& numbers, int idx) {
        int current = numbers[idx];
        int res = std::numeric_limits<int>::max();

        for(auto it = std::upper_bound(numbers.begin(),numbers.begin() + idx, current/2); 
        it != numbers.end(); it++) {
            if(*it * 2 > current) {
                res = std::min(*it * 2,res);
                break;
            }
        }
        for(auto it = std::upper_bound(numbers.begin(),numbers.begin() + idx, current/3); 
        it != numbers.end(); it++) {
            if(*it * 3 > current) {
                res = std::min(*it * 3,res);
                break;
            }
        }
        for(auto it = std::upper_bound(numbers.begin(),numbers.begin() + idx, current/5); 
        it != numbers.end(); it++) {
            if(*it * 5 > current) {
                res = std::min(*it * 5,res);
                break;
            }
        }
        return res;
    }
    
    int nthUglyNumberNaive(int n) {
        std::vector<int> numbers(n+1);
        numbers[1] = 1;
        for(size_t i = 2; i < numbers.size(); i++) {
            numbers[i] = find_next(numbers,i-1);
        }
#ifdef DEBUG
        for(size_t i = 0; i < numbers.size(); i++) {
            std::cerr << numbers[i] << ' ';
        }
        std::cerr << std::endl;
#endif
        return numbers.back();
    }

    // Quite slow
    int nthUglyNumber(int n) {
        std::vector<int> heapq;
        heapq.push_back(1);

        auto res = heapq.front();
        while(n--) {
            res = heapq.front();
            std::pop_heap(heapq.begin(),heapq.end(),std::greater<int>());
            heapq.erase(prev(heapq.end()));
            if(res < 1073741824) {
                if(std::find(heapq.begin(),heapq.end(),res * 2) == heapq.end()) {
                    heapq.push_back(res * 2);
                    std::push_heap(heapq.begin(),heapq.end(),std::greater<int>());
                }
            }
            if(res < 716636160) {
                if(std::find(heapq.begin(),heapq.end(),res * 3) == heapq.end()) {
                    heapq.push_back(res * 3);
                    std::push_heap(heapq.begin(),heapq.end(),std::greater<int>());
                }
            }
            if(res < 429981696) {
                if(std::find(heapq.begin(),heapq.end(),res * 5) == heapq.end()) {
                    heapq.push_back(res * 5);
                    std::push_heap(heapq.begin(),heapq.end(),std::greater<int>());
                }
            }
        }

        return res;
    }

#if 0 // Extremely elegant solution from discussions
    int nthUglyNumber(int n) {
        int nm2,nm3,nm5;//To store next multiples of 2,3 and 5
        int i2=0,i3=0,i5=0;
        vector<int>dp(1691);
        dp[0]=1;
        for(int i=1;i<n;i++)
        {
            nm2=dp[i2]*2;
            nm3=dp[i3]*3;
            nm5=dp[i5]*5;
            dp[i]=min(nm2,min(nm3,nm5));
            if(dp[i]==nm2) i2++;//next multiple of 2 of number at pos i2 has been included
            if(dp[i]==nm3) i3++;//next multiple of 3 of number at pos i3 has been included
            if(dp[i]==nm5) i5++;//next multiple of 5 of number at pos i5 has been included
        }
        return dp[n-1];
    }
#endif
};

int main(void) {
    std::cout << Solution().nthUglyNumber(1600) << std::endl;
    return 0;
}