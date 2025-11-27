#include<iostream>
#include<queue>
#include<utility>
using namespace std;

/*若要使用DFS广度优先搜索，可以在traverse函数的参数中记录当前节点的深度和当前节点的编号*/

struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void levelOrderTraversal(TreeNode* root) {
    if(!root) return;
    queue<pair<TreeNode*, int>> q;
    q.push(pair(root,1));
    while(!q.empty()) {
        int sz = q.size();
        int start=0,end=0;
        for(int i = 0; i < sz; ++i) {
            pair<TreeNode*, int> node = q.front();
            q.pop();
            if(i == 0) start = node.second; // 记录每层的起始编号
            if(i == sz - 1) end = node.second; // 记录每层的结束编号
            if(node.first->left) {
                q.push(pair(node.first->left, node.second * 2));
            }
            if(node.first->right) {
                q.push(pair(node.first->right, node.second * 2 + 1));
            }
        }
        cout << "Level width: " << end - start + 1 << endl; // 输出每层的宽度
    }
}

void traverse(TreeNode* root, int depth, int index, int &max_depth) {
    if(!root) return;
    // 处理当前节点
    cout << "Depth: " << depth << ", Index: " << index << ", Value: " << root->val << endl;
    if(depth > max_depth) {
        max_depth = depth;
    }
    // 遍历左子树
    traverse(root->left, depth + 1, index * 2, max_depth);
    // 遍历右子树
    traverse(root->right, depth + 1, index * 2 + 1, max_depth);
}