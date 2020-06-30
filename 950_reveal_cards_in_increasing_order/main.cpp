#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>

class Solution {
public:
    std::vector<int> deckRevealedIncreasing(std::vector<int>& deck) {
        std::sort(deck.begin(),deck.end());
        
        std::vector<int> ans(deck.size());
        std::deque<int*> simulation(deck.size());
        
        for(size_t i = 0, j = 0; i < deck.size(); i ++) {
            if(i % 2) {
                ans[i] = -1;
            } else {
                ans[i] = deck[j++];
            }
            simulation[i] = &ans[i];
        }
        
        size_t second_half_idx = (deck.size() % 2 == 0) ? deck.size()/2 : deck.size()/2 + 1;
        while(!simulation.empty()) {
            if(*simulation.front() == -1) {
                *simulation.front() = deck[second_half_idx++];
            }
            simulation.pop_front();
            simulation.push_back(simulation.front());
            simulation.pop_front();
        }
        
        return ans;
    }
};

int main(void) {
    std::vector<int> input = {17,13,11,2,3,5,7};
    for(auto i : Solution().deckRevealedIncreasing(input)) {
        std::cerr << i << ' ';
    }
    std::cerr << std::endl;
    return 0;
}