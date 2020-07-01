#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    void recurse(size_t idx, int num_opened, int num_closed, int n) {
        if(idx == current.size()) {
            ans.push_back(current);
            return;
        }
            
        if(num_opened > num_closed) {
            current[idx] = ')';
            recurse(idx+1,num_opened,num_closed+1,n);
        }
        if(num_opened < n) {
            current[idx] = '(';
            recurse(idx+1,num_opened+1,num_closed,n);
        }
    }
    
    std::vector<std::string> generateParenthesis(int n) {
        current.resize(n*2);
        current[0] = '(';
        recurse(1,1,0,n);
        return std::move(ans);
    }
private:
    std::string current;
    std::vector<std::string> ans;
};

int main(void) {
    for(const auto& s : Solution().generateParenthesis(3)) {
        std::cout << s << std::endl;
    }
    return 0;
}