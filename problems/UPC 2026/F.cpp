#include <iostream>
#include <string>
using namespace std;

int main(){
    string t;
    cin >> t;
    int len = t.size();
    
    // Count non-'a' characters in t
    int non_a = 0;
    for(char c : t) if(c != 'a') non_a++;
    
    // s has length len_s, s' has length len_s - count_a_in_s
    // len_s + (len_s - count_a_in_s) = len
    // We need to find len_s such that:
    // The first len_s chars form s, and removing 'a' from s gives the rest
    
    // non_a chars in t = non_a chars in s + non_a chars in s'
    // But s' = s without 'a', so non_a in s' = non_a in s
    // So non_a in t = 2 * non_a_in_s
    // So non_a must be even
    if(non_a % 2 != 0){
        cout << ":(" << "\n";
        return 0;
    }
    
    int non_a_in_s = non_a / 2;
    
    // Find len_s: scan t from left, count non-'a' until we have non_a_in_s of them
    // But also all chars count toward len_s
    // len_s = position where we've seen exactly non_a_in_s non-'a' chars
    // Actually: s has exactly non_a_in_s non-'a' chars. s can have any number of 'a's.
    // len_s + (len - len_s) = len, and len - len_s = length of s' = non_a_in_s
    // So len_s = len - non_a_in_s
    
    int len_s = len - non_a_in_s;
    
    if(len_s <= 0 || len_s > len){
        cout << ":(" << "\n";
        return 0;
    }
    
    string s = t.substr(0, len_s);
    string s_prime_expected = t.substr(len_s);
    
    // Verify: s without 'a' == s_prime_expected
    string s_prime = "";
    for(char c : s){
        if(c != 'a') s_prime += c;
    }
    
    if(s_prime == s_prime_expected){
        cout << s << "\n";
    } else {
        cout << ":(" << "\n";
    }
    
    return 0;
}
