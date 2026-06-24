#include <iostream>
#include <set>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        set<int> colors;
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            colors.insert(a);
        }
        // After the initial n cells, the fairy counts distinct colors = c
        // She paints cell n+1 with color c
        // If c is already in the set, nothing changes, all remaining cells get color c
        // If c is NOT in the set, she adds it, now count = c+1
        // Next cell gets color c+1, which is new, count becomes c+2, etc.
        // This continues until count equals the color being painted
        // Eventually stabilizes when c is already in the set
        // Simulate until stable (max ~1000 iterations since a_i <= 1000)
        int c = colors.size();
        while(colors.find(c) == colors.end()){
            colors.insert(c);
            c = colors.size();
        }
        cout << c << "\n";
    }
    return 0;
}
