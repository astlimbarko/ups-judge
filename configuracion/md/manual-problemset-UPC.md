# Manual para Crear Problemsets — UPC Judge (DOMjudge)

## Competencia: Entrenamiento UPC → Clasificatorio ICPC Regional

Este manual documenta el proceso completo para crear ejercicios de programación competitiva en formato DOMjudge, empaquetarlos y subirlos al servidor UPC Judge.

---

## Lenguajes Soportados en el Servidor

| Lenguaje | Versión | Extensión |
|----------|---------|-----------|
| C | GCC 13.3 | `.c` |
| C++ | GCC 13.3 | `.cpp` |
| Python | 3.12 | `.py` |
| Java | 21 | `.java` |
| Kotlin | 1.9 | `.kt` |

> Según la especificación ICPC, se requiere **al menos una** solución de referencia (jury solution) en cualquiera de estos lenguajes. No es necesario proveer una solución por cada lenguaje. Se recomienda C++ por ser el más rápido y estándar en competencias ICPC.

---

## Estructura de Carpetas de un Problema

Cada problema es una carpeta con una letra como nombre. Estructura interna:

```
A/
├── domjudge-problem.ini       ← Configuración DOMjudge (nombre, color, permisos)
├── problem.yaml               ← Metadatos ICPC (límites de tiempo/memoria)
├── problem.pdf                ← Enunciado en PDF (visible para equipos)
├── data/
│   ├── sample/                ← Casos de prueba VISIBLES para equipos
│   │   ├── 1.in
│   │   └── 1.ans
│   └── secret/                ← Casos de prueba OCULTOS (para el juez)
│       ├── 1.in
│       ├── 1.ans
│       ├── 2.in
│       ├── 2.ans
│       ├── 3.in
│       └── 3.ans
└── submissions/
    └── accepted/              ← Al menos 1 solución correcta (jury solution)
        └── solucion.cpp       (o .py, .java, .kt, .c — cualquier lenguaje)
```

### Reglas clave:
- El **nombre de la carpeta** (`A`, `B`, `C`...) se convierte en el short-name del scoreboard.
- `data/sample/` → ejemplos visibles para los competidores.
- `data/secret/` → casos de evaluación ocultos.
- Debe haber **al menos 1 testcase secreto** para que DOMjudge evalúe el problema.
- Se requiere **al menos 1 jury solution** en `submissions/accepted/` (spec ICPC).
- Los archivos `.in` y `.ans` deben terminar con un salto de línea (LF, no CRLF).
- El enunciado va como `problem.pdf` (DOMjudge lo muestra a los equipos directamente).

---

## Archivo `domjudge-problem.ini`

Archivo principal que DOMjudge lee para configurar el problema. **Obligatorio**.

```ini
name = Koshary
timelimit = 1
color = #FF8C00
allow_submit = 1
allow_judge = 1
```

### Campos:

| Campo | Descripción | Valor típico |
|-------|-------------|--------------|
| `name` | Nombre visible del problema | `Suma Simple` |
| `timelimit` | Tiempo límite en segundos | `1` o `2` |
| `color` | Color hex del problema | `#FF8C00` |
| `allow_submit` | Permitir envíos (1=sí, 0=no) | `1` |
| `allow_judge` | Permitir evaluación (1=sí, 0=no) | `1` |

### Paleta de colores sugerida (10 problemas):

| Letra | Color | Hex |
|-------|-------|-----|
| A | Rojo | `#FF0000` |
| B | Azul | `#0000FF` |
| C | Verde | `#008000` |
| D | Dorado | `#FFD700` |
| E | Púrpura | `#800080` |
| F | Rosa | `#FF69B4` |
| G | Negro | `#000000` |
| H | Naranja | `#FF8C00` |
| I | Marrón | `#8B4513` |
| J | Celeste | `#00BFFF` |

---

## Archivo `problem.yaml`

Formato estándar ICPC para metadatos del problema.

```yaml
name: Koshary
limits:
  time_limit: 1
  memory: 256
```

| Campo | Descripción |
|-------|-------------|
| `name` | Nombre del problema |
| `limits.time_limit` | Tiempo límite en segundos |
| `limits.memory` | Memoria máxima en MB (típico: 256) |

> No incluir `color` ni `rgb` aquí. DOMjudge los ignora en este archivo.

---

## Casos de Prueba (Testcases)

### Formato:
- `.in` → entrada que recibe el programa
- `.ans` → salida esperada (correcta)
- Numeración: `1.in`/`1.ans`, `2.in`/`2.ans`, `3.in`/`3.ans`...
- Texto plano, sin BOM, con salto de línea al final del archivo
- La comparación es **exacta** (carácter a carácter)

### Recomendaciones para casos secretos:
- Mínimo 3 casos secretos por problema
- Incluir: caso mínimo, caso típico, caso límite (valores máximos)
- Para problemas con múltiples testcases internos (t casos), incluir un caso con t máximo
- Cubrir edge cases: valores negativos, ceros, strings vacíos según aplique

### Ejemplo (`data/sample/1.in`):
```
6
1 1
1 2
4 6
5 9
7 2
10 10
```

### Ejemplo (`data/sample/1.ans`):
```
NO
YES
YES
NO
YES
YES
```

---

## Soluciones de Referencia (Jury Solutions)

Van en `submissions/accepted/`. DOMjudge las ejecuta al importar para validar que los testcases son correctos. **Se requiere mínimo 1** en cualquier lenguaje soportado.

Al subir el ZIP, si `allow_submit = 1` y el usuario admin tiene un equipo asociado, DOMjudge envía automáticamente estas soluciones como submissions del jurado. Si alguna falla, te alerta de que hay un error en los testcases.

### Plantilla C++ (`solucion.cpp`):
```cpp
#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        // Leer entrada
        // Procesar
        // Imprimir salida
    }
    return 0;
}
```

### Plantilla Python (`solucion.py`):
```python
t = int(input())
for _ in range(t):
    # Leer entrada
    # Procesar
    # Imprimir salida
    pass
```

### Plantilla Java (`Solucion.java`):
```java
import java.util.Scanner;

public class Solucion {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            // Leer entrada
            // Procesar
            // Imprimir salida
        }
    }
}
```

### Plantilla Kotlin (`solucion.kt`):
```kotlin
fun main() {
    val t = readLine()!!.trim().toInt()
    repeat(t) {
        // Leer entrada
        // Procesar
        // Imprimir salida
    }
}
```

> **Importante:** Para que las jury solutions se envíen automáticamente, el usuario admin debe tener un equipo asociado en DOMjudge.

---

## Enunciado del Problema

El enunciado se incluye como `problem.pdf` dentro de la carpeta del problema. DOMjudge lo muestra directamente a los equipos cuando hacen clic en el problema.

Formatos aceptados por DOMjudge: `problem.pdf`, `problem.html`, `problem.txt` (solo uno es necesario). **Usamos PDF** porque es el formato estándar ICPC y no se puede alterar por los competidores.

---

## Generar ZIPs y Subir al Servidor

### Script `generar-y-subir.sh`:

```bash
#!/bin/bash
API_URL="http://TU_IP_SERVIDOR/api/v4"
CID="nombre_contest"
USER="admin"
PASS="TU_PASSWORD"

ZIP_DIR="./zips"
mkdir -p "$ZIP_DIR"

echo "========================================="
echo " Generando ZIPs y subiendo a DOMjudge"
echo "========================================="

# Verificar conexión
RESPONSE=$(curl -s -o /dev/null -w "%{http_code}" -u "$USER:$PASS" "$API_URL/contests/$CID")
if [ "$RESPONSE" != "200" ]; then
    echo "ERROR: No se pudo conectar. HTTP: $RESPONSE"
    exit 1
fi
echo "Conexión OK!"

# Generar ZIPs
for dir in A B C D E F G H I J; do
    if [ -d "$dir" ]; then
        rm -f "$ZIP_DIR/$dir.zip"
        cd "$dir"
        zip -r "../$ZIP_DIR/$dir.zip" . -x ".*"
        cd ..
        echo "Generado: $dir.zip"
    fi
done

# Subir ZIPs
for zip in "$ZIP_DIR"/*.zip; do
    FILENAME=$(basename "$zip")
    echo "Subiendo: $FILENAME"
    RESULT=$(curl -s -u "$USER:$PASS" -F "zip=@$zip" "$API_URL/contests/$CID/problems")
    echo "  Respuesta: $RESULT"
done

echo "========================================="
echo " ¡Listo!"
echo "========================================="
```

### Ejecución (en el servidor Linux):
```bash
cd /ruta/a/problems
sed -i 's/\r$//' generar-y-subir.sh    # Convertir si fue creado en Windows
chmod +x generar-y-subir.sh
./generar-y-subir.sh
```

---

## Checklist para Crear un Problema Nuevo

- [ ] Crear carpeta con la letra (ej: `A/`)
- [ ] Crear `domjudge-problem.ini` con: name, timelimit, color, allow_submit=1, allow_judge=1
- [ ] Crear `problem.yaml` con: name, limits (time_limit y memory)
- [ ] Crear `data/sample/1.in` y `data/sample/1.ans` (caso ejemplo visible)
- [ ] Crear `data/secret/1.in`, `1.ans`, `2.in`, `2.ans`, `3.in`, `3.ans` (casos ocultos)
- [ ] Crear `submissions/accepted/solucion.cpp` (al menos 1 solución correcta en cualquier lenguaje)
- [ ] Incluir `problem.pdf` con el enunciado
- [ ] Verificar que todos los `.in` y `.ans` terminan con salto de línea (LF)
- [ ] Verificar que los colores sean distintos entre problemas
- [ ] Probar localmente que la solución produce las salidas esperadas
- [ ] Agregar la letra al script de subida

---

## Problemas Comunes y Soluciones

| Problema | Causa | Solución |
|----------|-------|----------|
| Problemas no visibles | `allow_submit = 0` o no está | Verificar `domjudge-problem.ini` |
| Testcases no detectados | ZIP creado en Windows | Generar ZIPs en Linux |
| Script falla en Linux | CRLF (Windows) | `sed -i 's/\r$//' script.sh` |
| Jury solutions no se envían | Admin sin equipo asociado | Asociar equipo al admin |
| Colores no aparecen | Falta `color` en .ini | Agregar `color = #HEXCODE` |
| Wrong Answer inesperado | Espacio o newline extra | Revisar `.ans` carácter a carácter |
| TLE en Python | Python es ~10x más lento | Considerar timelimit de 2-3s si hay solución Python |
| Kotlin no compila | Clase con main incorrecto | Usar `fun main()` top-level |
| Java no compila | Nombre de clase no coincide | El nombre de clase debe coincidir con el archivo |

---

## Notas Importantes

1. **Siempre generar ZIPs en Linux**, no en Windows. Windows usa backslash en rutas y DOMjudge no los reconoce.
2. El nombre del ZIP (sin extensión) se usa como identificador corto en el scoreboard.
3. Si re-subes un ZIP con el mismo nombre, DOMjudge **actualiza** el problema (no duplica).
4. Si subes con nombre nuevo, DOMjudge **crea** un problema nuevo.
5. Para el ICPC Regional: los problemas suelen tener timelimit 1-3s y memory 256MB.
6. Para Python 3.12: considerar que es más lento que C++, ajustar timelimit si la solución esperada es en Python.
7. Para Kotlin 1.9: el startup time es alto, considerar +1s extra si se espera que participantes usen Kotlin.

---

## Flujo Completo para la Competencia UPC

```
1. Obtener/redactar enunciados en PDF
2. Crear al menos 1 solución de referencia correcta (jury solution)
3. Generar testcases (sample + secretos) y verificar con la solución
4. Armar estructura de carpetas (A/, B/, C/...)
5. Crear domjudge-problem.ini y problem.yaml
6. Colocar problem.pdf en cada carpeta
7. Probar localmente que la solución produce las salidas esperadas
8. Copiar generar-y-subir.sh junto a las carpetas A, B, C...
9. Subir al servidor Linux y ejecutar el script
10. Verificar desde el panel admin que todo funcione
11. Hacer un contest de prueba antes del día oficial
```

---

*Manual actualizado — Junio 2026*
*Servidor: DOMjudge con C (GCC 13.3), C++ (GCC 13.3), Python 3.12, Java 21, Kotlin 1.9*
