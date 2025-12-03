#include <iostream>
#include <vector>
#include <climits>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main() {
    int n;
    cin >> n;
    vector<int> weight(n + 1, 0);
    vector<ll> prefix(n + 1, 0);
    for(int i = 0; i < n; i++) {
        cin >> weight[i];
        prefix[i+1] = weight[i] + prefix[i];
    }
    // dp[i][j] 表示合并第i到第j个叶子节点所形成的子树的总权值最小和
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
    for(int i = 1; i <= n; i++) {
        dp[i][i] = weight[i];
    }
    for(int i = n; i >= 1; i--) {          // 从最后一行往上算
        for(int j = i + 1; j <= n; j++) {  // 只算 i < j 的部分(右上三角)
            dp[i][j] = INF;                // 初始化
            ll current_sum = prefix[j+1] - prefix[i]; // 计算当前区间和
            // 枚举分割点 k
            for(int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + current_sum);
            }
        }
    }
    cout << dp[1][n];
}

// 递归写法
vector<vector<ll>> memo;
ll dp(const vector<int>& weight,int i,int j){
    if(i>j) return 0;
    if(i==j) return weight[i];
    if(memo[i][j]!=-1) return memo[i][j];
    ll res=LLONG_MAX;
    for(int k=i;k<j;k++){
        ll current_sum=0;
        for(int m=i;m<=j;m++){
            current_sum+=weight[m];
        }
        res=min(res,dp(weight,i,k)+dp(weight,k+1,j)+current_sum);
    }
    return res;
}