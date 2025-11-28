#include <bits/stdc++.h>
using namespace std;
class TreeNode {
  public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return find(root, p->val, q->val);
    }

    TreeNode* find(TreeNode* root, int val1, int val2) {
        if (root == nullptr) {
            return nullptr;
        }
        // 如果已经找到 LCA 节点，直接返回nullptr，避免继续递归
        if (lca != nullptr) {
            return nullptr;
        }
        // 如果当前节点是其中一个目标节点，返回当前节点
        if (root->val == val1 || root->val == val2) {
            return root;
        }
        TreeNode* left = find(root->left, val1, val2);
        TreeNode* right = find(root->right, val1, val2);
        if (left != nullptr && right != nullptr) {
            // 当前节点是 LCA 节点，记录下来
            lca = root;
            return root;
        }
        else{
            return left != nullptr ? left : right;
        }
    }
private:
    // 用一个外部变量来记录是否已经找到 LCA 节点
    TreeNode* lca = nullptr;
};