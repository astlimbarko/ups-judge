#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        long long a, b, x;
        cin >> a >> b >> x;
        
        int ans = INT_MAX;
        
        // Estrategia: probar todos los posibles valores objetivo
        // Para a: podemos dividir a varias veces por x, obteniendo una secuencia de valores
        // Para b: igual
        // Para cada par de valores alcanzables, calcular el costo
        
        // Generar todos los valores alcanzables desde a dividiendo por x
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
        
        // Para cada valor objetivo v, el costo desde a es:
        //   dividir a hasta llegar a algun va <= v, luego sumar (v - va)
        //   total: divs_a + (v - va)
        // Igual para b.
        // Probamos todos los va y vb como objetivos
        
        for(auto& [va, opsA] : valsA){
            for(auto& [vb, opsB] : valsB){
                // Desde va, podemos sumar hasta llegar a vb, o viceversa
                // Pero solo podemos sumar (no restar)
                // Queremos que ambos lleguen al mismo valor
                // Si va <= vb: costo = opsA + opsB + (vb - va) -- a llega a va y suma hasta vb
                //              o bien opsA + opsB + (va - vb) si vb <= va
                if(va >= vb){
                    ans = min(ans, (int)(opsA + opsB + (va - vb)));
                } else {
                    ans = min(ans, (int)(opsA + opsB + (vb - va)));
                }
            }
        }
        
        cout << ans << "\n";
    }
    return 0;
}
