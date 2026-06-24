#include <iostream>
#include <set>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        long long a, b, l;
        cin >> a >> b >> l;
        set<long long> ks;
        // Try all possible x and y such that a^x * b^y divides l
        long long ax = 1;
        while(ax <= l){
            long long by = 1;
            while(ax * by <= l){
                if(l % (ax * by) == 0){
                    ks.insert(l / (ax * by));
                }
                by *= b;
            }
            ax *= a;
        }
        cout << ks.size() << "\n";
    }
    return 0;
}
