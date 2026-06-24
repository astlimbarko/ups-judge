#include <iostream>
#include <set>
using namespace std;

int main(){
    int p, n;
    cin >> p >> n;
    set<int> used;
    int ans = -1;
    for(int i = 1; i <= n; i++){
        long long x;
        cin >> x;
        int h = x % p;
        if(used.count(h)){
            ans = i;
            break;
        }
        used.insert(h);
    }
    // Leer el resto de la entrada
    cout << ans << "\n";
    return 0;
}
