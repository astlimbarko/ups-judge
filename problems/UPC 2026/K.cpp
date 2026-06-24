#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> c(n);
    for(int i = 0; i < n; i++) cin >> c[i];
    
    // Compress into segments of same color
    vector<int> segs;
    segs.push_back(c[0]);
    for(int i = 1; i < n; i++){
        if(c[i] != segs.back()) segs.push_back(c[i]);
    }
    
    int m = segs.size();
    if(m == 1){
        cout << 0 << "\n";
        return 0;
    }
    
    // DP: dp[i][j] = min operations to make segment i..j all one color
    // Transition: dp[i][j] = dp[i+1][j] + 1 (merge i into i+1..j result)
    // But if segs[i] == segs[j], dp[i][j] = dp[i][j-1] (merging j is free once i..j-1 reaches segs[i])
    // Actually: dp[i][j] = dp[i+1][j-1] + 1 if segs[i]==segs[j]... no.
    // 
    // Standard flood fill DP on intervals:
    // dp[i][j] = min turns to make all segments i..j same color
    // dp[i][i] = 0
    // dp[i][j] = dp[i+1][j] + 1 (paint segment i to match whatever i+1..j becomes)
    // optimization: if segs[i] == segs[k] for some k in (i,j], then:
    //   dp[i][j] = dp[i][k] + dp[k+1][j] ... no this isn't right either.
    //
    // Correct DP for this problem:
    // dp[i][j] = min turns to make segments i to j all one color, starting from any segment in [i,j]
    // dp[i][i] = 0
    // dp[i][j] = dp[i+1][j] + 1 = dp[i][j-1] + 1
    // If segs[i] == segs[j], dp[i][j] = dp[i+1][j-1] + 1... actually
    // dp[i][j] = dp[i+1][j-1] + 1 when segs[i]==segs[j] because when the middle reaches one color
    //            and you paint it to segs[i], both ends merge simultaneously.
    // 
    // Let me use the standard:
    // dp[i][j] = dp[i][j-1] + 1 (expand right: need one more turn)
    // For all k in [i, j-1] where segs[k] == segs[j]: dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j-1])
    // Wait, the standard CF editorial for flood fill:
    // dp[i][j] = minimum moves to reduce segments i..j to a single segment
    // dp[i][j] = dp[i+1][j] + 1
    // If segs[i] == segs[j]: dp[i][j] = min(dp[i][j], dp[i+1][j-1] + 1)
    // More generally: if segs[i] == segs[k]: dp[i][j] = min(dp[i][j], dp[i+1][k] + dp[k][j])
    //   because once i+1..k becomes same color as k (which = segs[i]), the i merges for free.
    //   Wait, dp[i+1][k] makes i+1..k one color. If that color equals segs[i], then i merges.
    //   And dp[k][j] makes k..j one color. But i+1..k includes k...
    //
    // Cleaner approach: standard interval DP for this problem:
    // dp[l][r] = min turns to unify segments l..r
    // dp[l][l] = 0
    // dp[l][r] = dp[l+1][r] + 1
    // If segs[l] == segs[k] for l < k <= r:
    //   dp[l][r] = min(dp[l][r], dp[l+1][k] + dp[k][r])
    // The idea: dp[l+1][k] turns to merge l+1..k into one segment. Since segs[l]==segs[k],
    // when segment k absorbs everything between l+1 and k, segment l merges for free.
    // Then dp[k][r] to merge k..r (now including l).
    
    vector<vector<int>> dp(m, vector<int>(m, 0));
    
    for(int len = 2; len <= m; len++){
        for(int l = 0; l + len - 1 < m; l++){
            int r = l + len - 1;
            dp[l][r] = dp[l+1][r] + 1;
            for(int k = l+1; k <= r; k++){
                if(segs[k] == segs[l]){
                    int val = dp[l+1][k] + dp[k][r];
                    dp[l][r] = min(dp[l][r], val);
                }
            }
        }
    }
    
    cout << dp[0][m-1] << "\n";
    return 0;
}
