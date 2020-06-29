
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/// TODO: impement a balanced BST solution
class Solution {
public:
    TreeNode* dfs(TreeNode* root, int val) {
        if(root->val < val) {
            if(root->right) {
                return dfs(root->right,val);
            } else {
                root->right = new TreeNode(val);
                return root->right;
            }
        } else {
            if(root->left) {
                return dfs(root->left,val);
            } else {
                root->left = new TreeNode(val);
                return root->left;
            }
        }
        return nullptr;
    }
    
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root)
            dfs(root,val);
        else
            root = new TreeNode(val);
        return root;
    }
};