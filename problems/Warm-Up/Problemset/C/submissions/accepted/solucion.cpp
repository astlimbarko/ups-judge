#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < n; i++) cin >> b[i];

        int iterations = 0;
        while(true){
            bool found1 = false;
            for(int i = 0; i < n; i++){
                if(a[i] > b[i]){
                    a[i]--;
                    found1 = true;
                    break;
                }
            }

            for(int i = 0; i < n; i++){
                if(a[i] < b[i]){
                    a[i]++;
                    break;
                }
            }

            iterations++;

            if(!found1) break;
        }

        cout << iterations << "\n";
    }
    return 0;
}
