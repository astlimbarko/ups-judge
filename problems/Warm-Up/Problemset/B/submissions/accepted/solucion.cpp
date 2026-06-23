#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;

        // Expandir: rellenar gaps de 1 entre dos 1's iterativamente
        string maxS = s;
        bool changed = true;
        while(changed){
            changed = false;
            for(int i = 1; i < n - 1; i++){
                if(maxS[i] == '0' && maxS[i-1] == '1' && maxS[i+1] == '1'){
                    maxS[i] = '1';
                    changed = true;
                }
            }
        }
        int maxOnes = count(maxS.begin(), maxS.end(), '1');

        // Minimo: en cada bloque de 1's consecutivos de longitud k, min = k/2 + 1
        int minOnes = 0;
        int blockLen = 0;
        for(int i = 0; i < n; i++){
            if(maxS[i] == '1'){
                blockLen++;
            } else {
                if(blockLen > 0){
                    minOnes += blockLen / 2 + 1;
                    blockLen = 0;
                }
            }
        }
        if(blockLen > 0){
            minOnes += blockLen / 2 + 1;
        }

        cout << minOnes << " " << maxOnes << "\n";
    }
    return 0;
}
