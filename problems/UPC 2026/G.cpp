#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<int> pos, neg;
        for(int i = 0; i < n; i++){
            int x;
            cin >> x;
            if(x > 0) pos.push_back(x);
            else if(x < 0) neg.push_back(-x);
        }
        sort(pos.rbegin(), pos.rend());
        sort(neg.rbegin(), neg.rend());
        
        long long dist = 0;
        
        // Process positive depots: take k at a time, farthest first
        // Each trip covers distance 2 * farthest in group, except possibly the last trip
        for(int i = 0; i < (int)pos.size(); i += k){
            dist += 2LL * pos[i];
        }
        
        // Process negative depots: same logic
        for(int i = 0; i < (int)neg.size(); i += k){
            dist += 2LL * neg[i];
        }
        
        // We don't need to return after the last delivery
        // The optimal is to not return from the farthest overall trip
        long long farthest = 0;
        if(!pos.empty()) farthest = max(farthest, (long long)pos[0]);
        if(!neg.empty()) farthest = max(farthest, (long long)neg[0]);
        
        dist -= farthest;
        
        cout << dist << "\n";
    }
    return 0;
}
