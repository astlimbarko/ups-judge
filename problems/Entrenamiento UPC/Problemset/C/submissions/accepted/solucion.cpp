#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string row1, row2;
        cin >> row1 >> row2;
        
        // dp[i] = min repintados considerando columnas i..n-1
        // Opcion 1: emparejar columna i verticalmente
        // Opcion 2: emparejar columnas i,i+1 horizontalmente
        
        vector<int> dp(n + 1, 0);
        for (int i = n - 1; i >= 0; i--) {
            int vert_cost = (row1[i] != row2[i]) ? 1 : 0;
            int best = vert_cost + dp[i + 1];
            
            if (i + 1 < n) {
                int horiz_cost = (row1[i] != row1[i+1] ? 1 : 0) + (row2[i] != row2[i+1] ? 1 : 0);
                best = min(best, horiz_cost + dp[i + 2]);
            }
            
            dp[i] = best;
        }
        
        cout << dp[0] << "\n";
    }
    return 0;
}
