#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        long long n, rk, ck, rd, cd;
        cin >> n >> rk >> ck >> rd >> cd;
        
        long long ans;
        if(rd <= rk && cd <= ck){
            if(rk == rd)
                ans = n - cd;
            else if(ck == cd)
                ans = n - rd;
            else
                ans = max(n - cd, n - rd);
        }
        else if(rd >= rk && cd >= ck){
            if(rk == rd)
                ans = cd;
            else if(ck == cd)
                ans = rd;
            else
                ans = max(cd, rd);
        }
        else if(rd <= rk && cd >= ck){
            if(rk == rd)
                ans = cd;
            else if(ck == cd)
                ans = n - rd;
            else
                ans = max(n - rd, cd);
        }
        else{
            if(rk == rd)
                ans = n - cd;
            else if(ck == cd)
                ans = rd;
            else
                ans = max(rd, n - cd);
        }
        
        cout << ans << "\n";
    }
    return 0;
}
