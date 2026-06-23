#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        long long a, b, x;
        cin >> a >> b >> x;

        vector<pair<long long, int>> valsA, valsB;
        {
            long long cur = a;
            int ops = 0;
            while(true){
                valsA.push_back({cur, ops});
                if(cur == 0) break;
                cur /= x;
                ops++;
            }
        }
        {
            long long cur = b;
            int ops = 0;
            while(true){
                valsB.push_back({cur, ops});
                if(cur == 0) break;
                cur /= x;
                ops++;
            }
        }

        long long ans = LLONG_MAX;
        for(auto& [va, opsA] : valsA){
            for(auto& [vb, opsB] : valsB){
                long long cost = (long long)opsA + opsB + abs(va - vb);
                ans = min(ans, cost);
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
