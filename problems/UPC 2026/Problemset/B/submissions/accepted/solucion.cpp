#include <iostream>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        long long n, f, a, b;
        cin >> n >> f >> a >> b;
        bool ok = true;
        long long prev = 0;
        for(int i = 0; i < n; i++){
            long long m;
            cin >> m;
            long long diff = m - prev;
            // Costo de mantener encendido: diff * a
            // Costo de apagar y encender: b
            long long cost = min(diff * a, b);
            f -= cost;
            if(f <= 0){
                ok = false;
            }
            prev = m;
        }
        cout << (ok ? "YES" : "NO") << "\n";
    }
    return 0;
}
