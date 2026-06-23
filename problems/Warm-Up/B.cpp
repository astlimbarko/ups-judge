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
        
        // Encontrar posiciones de todos los 1's
        vector<int> pos;
        for(int i = 0; i < n; i++){
            if(s[i] == '1') pos.push_back(i);
        }
        
        int ones = pos.size();
        
        if(ones <= 1){
            cout << ones << " " << ones << "\n";
            continue;
        }
        
        // Maximo: entre cada par de 1's consecutivos, si el gap es >= 1,
        // podemos rellenar todos los 0's entre ellos (porque los extremos son 1).
        // Pero la operación requiere que s[i-1]=s[i+1]=1, asi que se puede
        // propagar: si tenemos 1...1, podemos rellenar de afuera hacia adentro.
        // Sin embargo, hay una excepción: un gap de exactamente 1 (como "101")
        // ya tiene todo cubierto. Para gaps > 1, podemos rellenar todo.
        // Pero un gap de 1 ("10...01") solo puede rellenarse si es contiguo a 1's.
        // En realidad: la respuesta maxima es last1 - first1 + 1 MENOS
        // los gaps de exactamente 1 que NO se pueden rellenar? No...
        
        // Repensando: la operación permite cambiar s[i] a 0 o 1 si s[i-1]=s[i+1]=1.
        // Para maximizar: rellenamos 0's a 1's. Podemos rellenar s[i]=0 a 1 si
        // s[i-1]=1 y s[i+1]=1. Esto es iterativo: podemos expandir bloques de 1's.
        // Un gap de tamaño 1 entre dos 1's ("101" -> ya es 1) o "1X1" -> se rellena.
        // Un gap de tamaño 2: "1001" -> primero necesitamos "1X01" o "10X1" pero
        // ni X tiene vecinos ambos 1. No se puede rellenar un gap de tamaño >= 2?
        
        // Verifiquemos con el ejemplo: "011011" -> "011111" (segun la nota)
        // "011011": posiciones 1,2,4,5 son 1. Gap entre pos 2 y 4: size 1 (pos 3).
        // s[3] tiene s[2]=1 y s[4]=0... espera. s = "011011"
        // pos: 0='0', 1='1', 2='1', 3='0', 4='1', 5='1'
        // Para rellenar pos 3: necesitamos s[2]=1 y s[4]=1. Ambos son 1! -> rellena.
        // "011111" -> max ones entre rango = 5. Respuesta max = 5. Correcto!
        
        // "100101101" (n=9): s[0]='1',s[1]='0',s[2]='0',s[3]='1',s[4]='0',
        //                    s[5]='1',s[6]='1',s[7]='0',s[8]='1'
        // Posiciones de 1: 0, 3, 5, 6, 8
        // Gap entre 0 y 3: tamaño 2 (pos 1,2). Para rellenar pos 1: s[0]=1, s[2]=0. No.
        //   Para rellenar pos 2: s[1]=0, s[3]=1. No.
        //   No se puede rellenar este gap.
        // Gap entre 3 y 5: tamaño 1 (pos 4). s[3]=1, s[5]=1 -> SI se rellena.
        //   Ahora "100111101"
        // Gap entre 6 y 8: tamaño 1 (pos 7). s[6]=1, s[8]=1 -> SI se rellena.
        //   Ahora "100111111"
        // Total de 1's: pos 0 + pos 3-8 = 1 + 6 = 7. Correcto!
        
        // Entonces el maximo se obtiene rellenando gaps de tamaño 1 iterativamente.
        // Pero gaps de tamaño >= 2 no se pueden rellenar.
        
        // Algoritmo para maximo: simular el proceso de rellenar gaps de 1
        // entre dos 1's repetidamente hasta que no queden mas.
        
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
        
        // Minimo: podemos también poner 0's donde s[i-1]=s[i+1]=1.
        // Queremos minimizar los 1's.
        // Podemos poner 0's en posiciones rodeadas de 1's.
        // Esto reduce bloques de 1's consecutivos.
        // Un bloque de k 1's consecutivos (con ambos extremos no extendibles
        // porque están en los bordes o tienen 0's afuera) puede reducirse a:
        //   - Si los 1's en los extremos del bloque son posiciones internas (2<=i<=n-1):
        //     los extremos no se pueden tocar (no están entre dos 1's necesariamente)
        //   - Solo posiciones internas al bloque (no los extremos del bloque) se pueden cambiar
        //   - Pero al cambiar uno, puede permitir cambiar otros
        // Pensemos en un bloque "111...1" de longitud k:
        //   Los extremos del bloque no se pueden quitar (no tienen 1's en ambos lados fuera del bloque)
        //   Dentro del bloque: cada posicion interna tiene s[i-1]=1 y s[i+1]=1
        //   Podemos poner alternadamente 0's: "10101...01" -> ceil(k/2) unos
        //   Pero primero hay que expandir y luego minimizar en el string expandido.
        
        // Mejor enfoque: primero expandir al maximo, luego minimizar.
        // Sobre maxS, minimizar: en cada bloque de 1's consecutivos de longitud k,
        // el minimo de 1's es ceil(k/2) (patrón 101010...)
        // PERO los extremos del bloque no necesariamente se pueden tocar.
        // En maxS, un bloque de 1's de longitud k:
        //   - Si el bloque empieza en pos 0 o termina en pos n-1, esos extremos
        //     no se pueden quitar (pos 0 nunca tiene i-1, pos n-1 nunca tiene i+1)
        //   - Los extremos internos del bloque (donde hay 0 al lado) tampoco se quitan
        //     porque no tienen 1 de ambos lados.
        //   - Solo podemos quitar posiciones internas al bloque.
        //   - Minimo en un bloque de k: ceil(k/2)
        //   Wait, revisemos: bloque "111" (k=3): pos central tiene ambos lados 1, 
        //   lo ponemos a 0 -> "101". Los extremos no se tocan. min = 2 = ceil(3/2).
        //   Bloque "1111" (k=4): "1111" -> pos 1: s[0]=1,s[2]=1 -> "1011"
        //                         -> pos 2: s[1]=0,s[3]=1 -> no se puede.
        //                         Resultado: "1011" -> 3 unos. 
        //                         O: pos 2 primero: s[1]=1,s[3]=1 -> "1101"
        //                         -> pos 1: s[0]=1, s[2]=0 -> no. Resultado: "1101" -> 3.
        //                         Pero ceil(4/2)=2... eso no funciona.
        //   Hmm, let me reconsider.
        //   "1111": podemos hacer pos1=0 -> "1011", luego pos2: s[1]=0 -> no.
        //           o pos2=0 -> "1101", luego pos1: s[0]=1,s[2]=0 -> no.
        //   Min = 3? No. Intentemos: "1111" -> pos1=0 -> "1011" -> solo 3 unos.
        //   pos3 (si existe): "1011" s[2]=1,s[4]? fuera. No.
        //   Hmm para k=4 el min es 3? Pero enunciado dice para "111" (k=3) min=2.
        //   
        //   En realidad, para un bloque aislado de k 1's:
        //   Los extremos nunca se pueden quitar.
        //   Solo posiciones 2..k-1 (indexadas dentro del bloque) se pueden tocar.
        //   Pero al quitar una, puede que las vecinas ya no se puedan quitar.
        //   Patron optimo: mantener los extremos, y alternar 0's y 1's dentro.
        //   Bloque de k: resultado optimo = ceil(k/2) para k impar, ceil(k/2)+? 
        //   k=1: 1, k=2: 2, k=3: 2 (101), k=4: 3 (1011 or 1101), k=5: 3 (10101)
        //   k=6: 4 (101011? no... 101010 no porque extremos must be 1...)
        //   Wait. Bloque "111111" (k=6). Extremos fijos: pos 0 y 5 son 1.
        //   Podemos quitar pos 1: s[0]=1,s[2]=1 -> ok. "101111"
        //   Podemos quitar pos 3: s[2]=1,s[4]=1 -> ok. "101011"  
        //   Podemos quitar pos 4: s[3]=0... no.
        //   Resultado: "101011" = 4 unos. O: "101111"->"101011"->"101010"? 
        //   pos5 es extremo, can't touch. So "101011" -> pos4: s[3]=0, no.
        //   4 unos para k=6.
        //   Pattern: k=1->1, k=2->2, k=3->2, k=4->3, k=5->3, k=6->4
        //   Formula: ceil(k/2) + (k%2==0 ? 1 : 0)? No: 1,2,2,3,3,4 = ceil(k/2) + (k==2?1:0)?
        //   Actually that's just: (k+2)/2 for even? No. Let me just see:
        //   1->1, 2->2, 3->2, 4->3, 5->3, 6->4, 7->4
        //   That's ceil(k/2) for odd k, and k/2+1 for even k.
        //   Both simplify to: (k+1)/2 for odd, k/2+1 for even.
        //   Or: floor((k+2)/2) = (k/2)+1 for even, (k+1)/2 for odd.
        //   Hmm, simpler: for k>=1, min = floor(k/2) + 1? 
        //   k=1:1, k=2:2, k=3:2, k=4:3, k=5:3, k=6:4. Yes! floor(k/2)+1.
        //   Wait that's the same as ceil((k+1)/2). Let me verify: (1+1)/2=1, (2+1)/2=1.5->2,
        //   (3+1)/2=2, (4+1)/2=2.5->3, (5+1)/2=3, (6+1)/2=3.5->4. Yes!
        //   So min for a block of k = floor(k/2) + 1 = (k/2) + 1 (integer division).
        
        // Pero wait - primero hay que trabajar sobre el string ORIGINAL, no el expandido.
        // El minimo se calcula sobre el string original con las operaciones permitidas.
        // Podemos también AGREGAR 1's para poder quitar otros? Sí, el enunciado lo permite.
        // Ejemplo: "011011" -> "011111" -> "010111" -> "010101" = 3 unos (min).
        // Entonces sí, primero expandimos al máximo, luego minimizamos.
        
        // Calculemos el minimo sobre maxS:
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
