#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> sector(n + 1, 0);
    int points = 0;
    for(int i = 0; i < m; i++){
        int c;
        cin >> c;
        sector[c]++;
        // Verificar si todos los sectores tienen al menos 1
        bool allFull = true;
        for(int j = 1; j <= n; j++){
            if(sector[j] == 0){
                allFull = false;
                break;
            }
        }
        if(allFull){
            points++;
            for(int j = 1; j <= n; j++){
                sector[j]--;
            }
        }
    }
    cout << points << endl;
    return 0;
}
