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
        
        // Contar la suma de max(0, a[i] - b[i]) para todos i
        // Eso es cuanto tiene que bajar en total
        // Pero tambien en cada iteracion sube 1 si hay algun a[i] < b[i]
        // La palanca termina cuando no hay ningun a[i] > b[i]
        // Cada iteracion: baja 1 (si puede) y sube 1 (si puede)
        // Termina cuando no puede bajar (paso 1 ignorado)
        
        // Simulemos: dado que n <= 10 y valores <= 10, podemos simular
        int iterations = 0;
        while(true){
            // Paso 1: buscar algun i con a[i] > b[i]
            bool found1 = false;
            for(int i = 0; i < n; i++){
                if(a[i] > b[i]){
                    a[i]--;
                    found1 = true;
                    break;
                }
            }
            
            // Paso 2: buscar algun i con a[i] < b[i]
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
