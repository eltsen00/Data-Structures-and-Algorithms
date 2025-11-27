/*问题描述:
一个N×M的由非负整数构成的数字矩阵，你需要在其中取出若干个数字，使得取出的任意两个数字不相邻（若一个数字在另外一个数字相邻8个格子中的一个即认为这两个数字相邻），求取出数字和最大是多少。

输入：
第一行有两个正整数N和M，表示了数字矩阵为N行M列。
接下来N行，每行M个非负整数，描述了这个数字矩阵。

输出：一个非负整数，表示求得的结果*/

/*使用的位运算技巧：
1.mask&&(mask<<1)==0: 检查状态是否合法，即是否有相邻的位被选中
2.(mask>>j)&1: 检查第 j 位是否被选中
3.danger_zone=prev_mask|(prev_mask>>1)|(prev_mask<<1): 计算前一行状态的危险区域
4.(mask&danger_zone)==0: 检查当前状态与前一行状态
5.limit=1<<M: 计算状态总数,2的M次方
*/
#include<iostream>
#include<vector>
using namespace std;
int main(){
    int N,M;
    cin>>N>>M;
    vector<vector<int>> matrix(N,vector<int>(M,0));
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>matrix[i][j];
        }
    }
    int limit=1<<M; // 计算状态总数,2的M次方
    // dp[i][mask] = 考虑到第 i 行，且第 i 行状态为 mask 时的最大和
    // 在状态压缩DP中，一个整数 mask（比如 20）被当作一个二进制数（比如 10100）来使用。我们只是用它来存储M个“是/否”的决定。
    // 动态规划（处理第0行）
    vector<vector<long long>> dp(N,vector<long long>(limit,0));
    for(int mask=0;mask<limit;mask++){
        if((mask&(mask<<1))==0){ // 检查状态是否合法，即是否有相邻的位被选中
            long long sum=0;
            for(int j=0;j<M;j++){
                if((mask>>j)&1){ // 如果第 j 位被选中
                    sum+=matrix[0][j];
                }
            }
            dp[0][mask]=sum;
        }
        else{
            dp[0][mask]=0; // 非法状态，和为0
            continue;
        }
    }
    // 动态规划 (处理第 1 到 N-1 行)
    for(int i=1;i<N;i++){ // 处理第 i 行
        for(int mask=0;mask<limit;mask++){ // 遍历所有可能的状态
            if((mask&(mask<<1))!=0){ // 检查状态是否合法
                dp[i][mask]=0;
                continue;
            }
            // 状态合法时，计算当前状态下当前行的和
            else{
                long long sum=0;
                for (int j=0;j<M;++j) {
                    if((mask>>j)&1){
                        sum+=matrix[i][j];
                    }
                }
                // 寻找与当前状态兼容的前一行状态，并计算最大和
                long long max_prev=0;
                for(int prev_mask=0;prev_mask<limit;prev_mask++){ // 遍历前一行的所有状态
                    if(dp[i-1][prev_mask]==0){ //去掉前一行已经发生了不兼容的
                        continue;
                    }
                    int danger_zone=prev_mask|(prev_mask>>1)|(prev_mask<<1); // 计算前一行状态的危险区域
                    if((mask&danger_zone)==0){ // 检查当前状态与前一行状态是否兼容
                        max_prev=max(max_prev,dp[i-1][prev_mask]);
                    }
                }
                dp[i][mask]=sum+max_prev;
            }
        }
    }
    // 找到最后一行的最大值
    long long max_sum=0;
    for (int mask=0;mask<limit;mask++){
        max_sum=max(max_sum,dp[N-1][mask]);
    }
    cout<<max_sum<<endl;
}