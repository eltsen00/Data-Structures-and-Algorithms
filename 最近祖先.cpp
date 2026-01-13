#include <iostream>
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
        // 1. 递归终止条件
        // 如果当前节点为空，或者当前节点就是我们要找的 p 或 q 之一
        // 那么直接返回当前节点（找到了，或者到底了都没找到）
        if(root == nullptr || root == p || root == q) {
            return root;
        }

        // 2. 递归查找左右子树
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        // 3. 处理查找结果
        // 情况 A: 如果左右两边都返回了非空值，说明 p 和 q 分别在当前节点的两侧
        // 此时当前节点 root 就是最近公共祖先
        if(left != nullptr && right != nullptr) {
            return root;
        }

        // 情况 B: 只有一边找到了（或者两边都没找到）
        // 结果就应该是那一边传上来的结果, 否则就是 nullptr
        return left != nullptr ? left : right;
    }
};

int main() {
    Solution solution;
    // 构建测试用例
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    TreeNode* p = root->left;                // 节点 5
    TreeNode* q = root->left->right->right;  // 节点 4
    TreeNode* lca = solution.lowestCommonAncestor(root, p, q);
    if(lca != nullptr) {
        cout << "LCA of " << p->val << " and " << q->val << " is: " << lca->val << endl;
    }
    else {
        cout << "LCA not found." << endl;
    }
}