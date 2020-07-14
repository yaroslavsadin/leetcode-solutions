#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <optional>

class Solution {
public:
    int longestCommonSubsequence(std::string text1, std::string text2) {
        std::vector<std::vector<int>> dp_matrix(text1.size() + 1,std::vector<int>(text2.size() + 1,0));
        
        for(size_t i = 1; i < dp_matrix.size(); i++) {
            for(size_t j = 1; j < dp_matrix[i].size(); j++) {
                if(text1[i-1] == text2[j-1]) {
                    dp_matrix[i][j] = dp_matrix[i-1][j-1] + 1;
                } else {
                    dp_matrix[i][j] = std::max(dp_matrix[i][j-1],dp_matrix[i-1][j]);
                }
            }
        }
#ifdef DEBUG
        std::cerr << ' ' << '\t';
        for(auto c : text2) {
            std::cerr << c << '\t';
        }
        std::cerr << std::endl;
        for(size_t i = 1; i < dp_matrix.size(); i++) {
            std::cerr << text1[i-1] << '\t';
            for(size_t j = 1; j < dp_matrix[i].size(); j++) {
                std::cerr << dp_matrix[i][j] << '\t';
            }
            std::cerr << std::endl;
        }
        std::cerr << std::endl;
#endif
        return dp_matrix.back().back();
    }
};

int main(void) {
    std::string text1 = "bsbininm";
    std::string text2 = "jmjkbkjkv";
    std::cout << Solution().longestCommonSubsequence(text1,text2) << std::endl;
    return 0;
}