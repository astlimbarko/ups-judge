#include <iostream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

// Calcular numero de permutaciones distintas
long long countPerms(const string& s) {
    int n = s.size();
    map<char, int> freq;
    for (char c : s) freq[c]++;
    
    long long num = 1;
    for (int i = 1; i <= n; i++) num *= i;
    for (auto& p : freq) {
        long long d = 1;
        for (int i = 1; i <= p.second; i++) d *= i;
        num /= d;
    }
    return num;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        
        long long minPerms = -1;
        string best = s;
        
        // Probar todas las operaciones posibles
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                string temp = s;
                temp[i] = s[j];
                long long p = countPerms(temp);
                if (minPerms == -1 || p < minPerms || (p == minPerms && temp < best)) {
                    minPerms = p;
                    best = temp;
                }
            }
        }
        
        cout << best << endl;
    }
    return 0;
}
