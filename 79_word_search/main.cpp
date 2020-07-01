#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

class Solution {
private:
    const char illegal = '#'; 
public:

    auto CheckNeighbors(vector<vector<char>>& board, size_t i, size_t j, char c) {
        std::vector<std::pair<int,int>> res;
        if(i != 0 && board[i-1][j] == c) {
            res.emplace_back(i-1,j);
        }
        if(j !=0 && board[i][j-1] == c) {
            res.emplace_back(i,j-1);
        }
        if(j != board[i].size() - 1 && board[i][j+1] == c) {
            res.emplace_back(i,j+1);
        }
        if(i != board.size() - 1 && board[i+1][j] == c) {
            res.emplace_back(i+1,j);
        }
        return res;
    }
    
    bool Recurse(vector<vector<char>>& board, size_t i, size_t j, std::string_view suffix) {
        suffix.remove_prefix(1);
        auto stacked = board[i][j];
        board[i][j] = illegal;
        if(suffix.empty()) {
            board[i][j] = stacked;
            return true;
        }
        auto matches = CheckNeighbors(board,i,j,suffix.front());
        for(const auto& match : matches) {
            if(Recurse(board,match.first,match.second,suffix)) {
                board[i][j] = stacked;
                return true;
            }
        }
        board[i][j] = stacked;
        return false;
    }
    
    bool exist(vector<vector<char>>& board, string word) {
        for(size_t i = 0; i < board.size(); i++) {
            for(size_t j = 0; j < board[i].size(); j++) {
                if(board[i][j] == word.front()) {
                    if(Recurse(board,i,j,word)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

int main(void) {
    vector<vector<char>> board =
    {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    std::cout << std::boolalpha << Solution().exist(board,"ABCB");
    return 0;
}