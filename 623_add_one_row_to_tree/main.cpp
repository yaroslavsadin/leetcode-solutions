#include <iostream>
#include <vector>


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    std::vector<TreeNode*> bfs(TreeNode* root, int d) {
        int level = 1;
        std::vector<TreeNode*> current_level_nodes;
        current_level_nodes.push_back(root);
        while(level < d) {
            std::vector<TreeNode*> next_level_nodes;
            for(auto* node : current_level_nodes) {
                if(node->left) {
                    next_level_nodes.push_back(node->left);
                }
                if(node->right) {
                    next_level_nodes.push_back(node->right);
                }
            }
            current_level_nodes = std::move(next_level_nodes);
            level++;
        }
        return current_level_nodes;
    }
    
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if(d == 1) {
            auto* root_old = root;
            root = new TreeNode(v, root_old, nullptr);
            return root;
        }
        auto nodes = bfs(root,d-1);
        for(auto* node : nodes) {
            auto* left_old = node->left;            
            auto* right_old = node->right;
            node->left = new TreeNode(v, left_old, nullptr);
            node->right = new TreeNode(v, nullptr, right_old);
        }
        return root;
    }
};