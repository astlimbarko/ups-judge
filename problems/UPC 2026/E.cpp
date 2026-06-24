#include <iostream>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        long long n, d;
        cin >> n >> d;
        // The number is d repeated n! times = d * repunit(n!) * 1
        // repunit(k) = (10^k - 1) / 9
        // Number = d * (10^(n!) - 1) / 9
        // Check divisibility by 1, 3, 5, 7, 9
        // 
        // By 1: always yes
        // By 5: number divisible by 5 iff d divisible by 5 (last digit is d)
        // By 3: digit sum = d * n!. Divisible by 3 iff d*n! % 3 == 0
        //        Since n >= 2, n! is always divisible by 2 and for n>=3 by 6
        //        For n>=3, n! % 3 == 0, so d*n! % 3 == 0 always
        //        For n==2, n!=2, so d*2 % 3 == 0 iff d % 3 == 0
        // By 9: digit sum = d * n!. Divisible by 9 iff d*n! % 9 == 0
        //        For n>=6, n! % 9 == 0 (since 6! = 720, 720%9=0), always yes
        //        For n>=3, n! has factor 3 at least once. d*n! % 9 == 0 depends.
        //        Actually: 3! = 6 (one factor of 3), 4!=24 (one 3), 5!=120 (one 3), 6!=720 (two 3s)
        //        n! % 9: need at least two factors of 3 in n!
        //        Legendre: v_3(n!) = floor(n/3) + floor(n/9) + ...
        //        For n>=6: v_3(6!) = 2+0 = 2, so 9 | n!. d*n! % 9 = 0
        //        For n=5: v_3(5!)=1, n!=120, 120%9=3. d*120%9 = d*3%9. div by 9 iff d%3==0
        //        For n=4: v_3(4!)=1, n!=24, 24%9=6. d*24%9 = d*6%9. div by 9 iff d*6%9==0
        //        For n=3: v_3(3!)=1, n!=6, 6%9=6. d*6%9. div by 9 iff d*6%9==0
        //        For n=2: n!=2, d*2%9==0 iff d*2%9==0
        // By 7: repunit(k) divisible by 7 iff k % 6 == 0 (since repunit(6) = 111111 = 7*15873)
        //        Number = d * repunit(n!)
        //        Div by 7 iff d%7==0 OR repunit(n!)%7==0
        //        repunit(n!) % 7 == 0 iff n! % 6 == 0 iff n >= 3
        //        For n=2: n!=2, repunit(2)=11, 11%7=4. So only if d%7==0
        
        bool results[5] = {false}; // for 1, 3, 5, 7, 9
        
        // By 1: always
        results[0] = true;
        
        // By 3: digit sum = d * n!. 
        // n! % 3: for n>=3, n!%3==0, so d*n!%3==0 always
        // for n==2, n!=2, d*2%3==0 iff d%3==0 (since gcd(2,3)=1)
        if(n >= 3){
            results[1] = true;
        } else {
            // n==2, check d*2 % 3
            results[1] = ((d * 2) % 3 == 0);
        }
        
        // By 5: last digit is d
        results[2] = (d % 5 == 0);
        
        // By 7: d * repunit(n!) % 7 == 0
        // repunit(k) % 7 == 0 iff k % 6 == 0
        // n! % 6: for n>=3, n!%6==0 (3!=6)
        // for n==2, n!=2, 2%6!=0, repunit(2)=11, 11%7=4
        if(n >= 3){
            results[3] = true;
        } else {
            // n==2: repunit(2)=11. d*11 % 7 == 0 iff d%7==0 (since 11%7=4, gcd(4,7)=1... wait)
            // Actually d*11 % 7. 11%7=4. So d*4%7==0 iff d%7==0
            results[3] = (d % 7 == 0);
        }
        
        // By 9: digit sum = d * n!
        // d * n! % 9 == 0
        // Compute n! % 9: for n>=6, n!%9==0
        // For smaller n: 2!=2, 3!=6, 4!=24%9=6, 5!=120%9=3
        long long nfact_mod9;
        if(n >= 6){
            nfact_mod9 = 0;
        } else if(n == 5){
            nfact_mod9 = 120 % 9; // = 3
        } else if(n == 4){
            nfact_mod9 = 24 % 9; // = 6
        } else if(n == 3){
            nfact_mod9 = 6 % 9; // = 6
        } else {
            nfact_mod9 = 2 % 9; // = 2
        }
        results[4] = ((d * nfact_mod9) % 9 == 0);
        
        int divisors[] = {1, 3, 5, 7, 9};
        bool first = true;
        for(int i = 0; i < 5; i++){
            if(results[i]){
                if(!first) cout << " ";
                cout << divisors[i];
                first = false;
            }
        }
        cout << "\n";
    }
    return 0;
}
