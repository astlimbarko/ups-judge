#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<long long> h(n);
        for(int i = 0; i < n; i++) cin >> h[i];
        
        // Each flower i reaches 0 at time = h[i] + (delay from flowers to its right blocking it)
        // A flower is blocked (doesn't decrease) when h[i] <= h[i+1]
        // The time for flower i to reach 0:
        // t[n-1] = h[n-1]
        // t[i] = max(h[i], t[i+1] + 1) -- if h[i] <= h[i+1], flower i gets delayed by 1 each tick after i+1
        // Actually: each second, h[i] decreases by 1 only if i==n-1 or h[i] > h[i+1]
        // The answer is the time when all reach 0.
        // t[i] = time for flower i to reach 0
        // t[n-1] = h[n-1] (always decreases)
        // For i < n-1: flower i decreases in a second if h[i] > h[i+1] at that moment
        // Key insight: t[i] = max(h[i], t[i+1] + 1)
        // because flower i needs h[i] seconds of "decreasing" time,
        // but it can only start its final countdown after i+1 is gone or lower.
        // Actually, simpler: flower i takes h[i] seconds to disappear IF it always decreases.
        // But it's blocked whenever h[i] <= h[i+1]. This means it must wait.
        // The formula: t[i] = max(h[i], t[i+1] + 1) because if flower i+1 takes t[i+1] to reach 0,
        // flower i is blocked until h[i+1] drops below h[i], adding at most 1 extra second.
        
        // Wait, let me reconsider. The correct formula based on the editorial of CF1993C:
        // t[n-1] = h[n-1]
        // t[i] = max(h[i], t[i+1] + 1) -- flower i can't finish before h[i] seconds,
        // and it also can't finish before t[i+1]+1 (it needs to be greater than h[i+1] to decrease)
        
        vector<long long> time_to_zero(n);
        time_to_zero[n-1] = h[n-1];
        for(int i = n-2; i >= 0; i--){
            time_to_zero[i] = max(h[i], time_to_zero[i+1] + 1);
        }
        
        cout << time_to_zero[0] << "\n";
    }
    return 0;
}
