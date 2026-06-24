#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int n = s.size();
        
        // Check for infinite: adjacent cells (i, i+1) where s[i] in ">*" and s[i+1] in "<*"
        bool infinite = false;
        for(int i = 0; i < n - 1; i++){
            if((s[i] == '>' || s[i] == '*') && (s[i+1] == '<' || s[i+1] == '*')){
                infinite = true;
                break;
            }
        }
        
        if(infinite){
            cout << -1 << "\n";
        } else {
            // Simulate from each starting position
            long long max_time = 0;
            for(int start = 0; start < n; start++){
                // Simulate
                int pos = start;
                long long time_taken = 0;
                bool hit_star = false;
                
                while(pos >= 0 && pos < n){
                    if(s[pos] == '<'){
                        pos--;
                        time_taken++;
                    } else if(s[pos] == '>'){
                        pos++;
                        time_taken++;
                    } else {
                        hit_star = true;
                        break;
                    }
                }
                
                if(hit_star){
                    // Try both directions
                    // Left
                    long long t1 = time_taken + 1;
                    int p = pos - 1;
                    while(p >= 0 && p < n){
                        if(s[p] == '<') p--;
                        else if(s[p] == '>') p++;
                        else p--; // fallback
                        t1++;
                    }
                    // Right
                    long long t2 = time_taken + 1;
                    p = pos + 1;
                    while(p >= 0 && p < n){
                        if(s[p] == '<') p--;
                        else if(s[p] == '>') p++;
                        else p++;
                        t2++;
                    }
                    max_time = max(max_time, max(t1, t2));
                } else {
                    max_time = max(max_time, time_taken);
                }
            }
            cout << max_time << "\n";
        }
    }
    return 0;
}
