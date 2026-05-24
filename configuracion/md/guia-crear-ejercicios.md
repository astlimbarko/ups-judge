# Guía: Cómo Crear un Ejercicio para UPC Judge (DOMjudge)

Esta guía documenta paso a paso cómo crear un problema de programación competitiva compatible con DOMjudge, empaquetarlo y subirlo al servidor.

---

## 1. Estructura de Carpetas

Cada ejercicio es una carpeta con una letra como nombre (A, B, C...). La estructura interna es:

```
A/
├── domjudge-problem.ini    ← Metadatos para DOMjudge (OBLIGATORIO)
├── problem.yaml            ← Metadatos ICPC (límites de tiempo/memoria)
├── problem.pdf             ← Enunciado en PDF (opcional, se muestra al equipo)
├── data/
│   ├── sample/             ← Casos de prueba VISIBLES para el equipo
│   │   ├── 1.in
│   │   └── 1.ans
│   └── secret/             ← Casos de prueba OCULTOS (para el juez)
│       ├── 1.in
│       ├── 1.ans
│       ├── 2.in
│       ├── 2.ans
│       ├── 3.in
│       └── 3.ans
└── submissions/
    └── accepted/           ← Soluciones de referencia (jury solutions)
        ├── solucion.cpp
        └── solucion.py
```

### Reglas importantes:
- El **nombre de la carpeta** (ej: `A`) será el **short name** del problema en el scoreboard.
- Los archivos en `data/sample/` son los que el equipo puede ver como ejemplo.
- Los archivos en `data/secret/` son los que el juez usa para evaluar (el equipo NO los ve).
- Debe haber **al menos 1 testcase** (sample o secret), sino DOMjudge desactiva el problema.

---

## 2. Archivo `domjudge-problem.ini`

Este es el archivo que DOMjudge realmente lee para configurar el problema. Es **obligatorio** para que funcionen los colores y el allow_submit.

```ini
name = Area de Rectangulo
timelimit = 1
color = #FF8C00
allow_submit = 1
allow_judge = 1
```

### Campos disponibles:

| Campo | Descripción | Ejemplo |
|-------|-------------|---------|
| `name` | Nombre visible del problema | `Suma Simple` |
| `timelimit` | Tiempo límite en segundos | `1` |
| `color` | Color CSS del problema (hex o nombre) | `#FF8C00`, `red` |
| `allow_submit` | Permitir envíos (1=sí, 0=no). Si es 0, el problema es INVISIBLE | `1` |
| `allow_judge` | Permitir juzgar (1=sí, 0=no) | `1` |
| `points` | Puntos del problema (default: 1) | `1` |
| `special_compare` | ID de comparador especial (opcional) | |
| `special_run` | ID de script de ejecución especial (opcional) | |

### Colores sugeridos para 10 problemas:

| Letra | Color | Hex |
|-------|-------|-----|
| A | Naranja | `#FF8C00` |
| B | Celeste | `#00BFFF` |
| C | Amarillo | `#FFD700` |
| D | Azul | `#0000FF` |
| E | Rojo | `#FF0000` |
| F | Rosa | `#FF69B4` |
| G | Negro | `#000000` |
| H | Morado | `#800080` |
| I | Verde | `#008000` |
| J | Marrón | `#8B4513` |

---

## 3. Archivo `problem.yaml`

Formato estándar ICPC. DOMjudge lo usa para leer los límites.

```yaml
name: Area de Rectangulo
limits:
  time_limit: 1
  memory: 256
```

| Campo | Descripción |
|-------|-------------|
| `name` | Nombre del problema |
| `limits.time_limit` | Tiempo límite en segundos |
| `limits.memory` | Memoria máxima en MB |

> **Nota:** NO pongas `color` ni `rgb` aquí. Esos campos no son parte del estándar ICPC y DOMjudge los ignora.

---

## 4. Casos de Prueba (Testcases)

### Formato:
- Archivo `.in` → entrada que se le da al programa
- Archivo `.ans` → salida esperada (correcta)
- Se numeran: `1.in`/`1.ans`, `2.in`/`2.ans`, etc.
- Deben estar en texto plano, sin BOM, con salto de línea al final

### Ejemplo - Problema "Área de Rectángulo":

**Entrada** (`data/sample/1.in`):
```
4 6
```

**Salida esperada** (`data/sample/1.ans`):
```
24
```

### Tips:
- Pon al menos 1 caso en `sample/` (para que el equipo vea un ejemplo).
- Pon 3-5 casos en `secret/` cubriendo: caso base, caso límite, caso grande.
- La comparación es **exacta** (carácter por carácter), así que cuida espacios y saltos de línea.

---

## 5. Soluciones de Referencia (Jury Solutions)

Dentro de `submissions/accepted/` pon soluciones que sabes que son correctas. DOMjudge las ejecuta automáticamente al importar para verificar que los testcases son válidos.

### Ejemplo C++ (`submissions/accepted/solucion.cpp`):
```cpp
#include <iostream>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;
    cout << a * b << endl;
    return 0;
}
```

### Ejemplo Python (`submissions/accepted/solucion.py`):
```python
a, b = map(int, input().split())
print(a * b)
```

> **Importante:** Para que las jury solutions se envíen automáticamente, el usuario admin debe tener un equipo asociado.

---

## 6. Enunciado del Problema

Puedes incluir el enunciado como:
- `problem.pdf` (recomendado)
- `problem.html`
- `problem.txt`

DOMjudge lo mostrará a los equipos cuando hagan clic en el problema.

---

## 7. Generar ZIPs y Subir al Servidor

### Requisitos en Ubuntu Server:
```bash
apt install zip curl -y
```

### Script `generar-y-subir.sh`:

```bash
#!/bin/bash
API_URL="http://192.168.42.130/api/v4"
CID="test1"
USER="admin"
PASS="TU_PASSWORD_AQUI"

ZIP_DIR="./zips"
mkdir -p "$ZIP_DIR"

echo "========================================="
echo " Generando ZIPs y subiendo a DOMjudge"
echo "========================================="

# Verificar conexion
RESPONSE=$(curl -s -o /dev/null -w "%{http_code}" -u "$USER:$PASS" "$API_URL/contests/$CID")
if [ "$RESPONSE" != "200" ]; then
    echo "ERROR: No se pudo conectar. HTTP: $RESPONSE"
    exit 1
fi
echo "Conexion OK!"

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
echo " Listo!"
echo "========================================="
```

### Ejecución:

```bash
# 1. Ir a la carpeta de problemas
cd /opt/upc-judge/ups-judge/problems

# 2. Convertir el script (si fue creado en Windows)
sed -i 's/\r$//' generar-y-subir.sh

# 3. Dar permisos de ejecución
chmod +x generar-y-subir.sh

# 4. Ejecutar
./generar-y-subir.sh
```

---

## 8. Checklist Rápido para Crear un Ejercicio Nuevo

- [ ] Crear carpeta con la letra (ej: `K/`)
- [ ] Crear `domjudge-problem.ini` con name, timelimit, color, allow_submit=1, allow_judge=1
- [ ] Crear `problem.yaml` con name y limits
- [ ] Crear `data/sample/1.in` y `data/sample/1.ans` (caso ejemplo)
- [ ] Crear `data/secret/1.in`, `1.ans`, `2.in`, `2.ans`, etc. (casos ocultos)
- [ ] Crear `submissions/accepted/solucion.cpp` y/o `solucion.py`
- [ ] (Opcional) Agregar `problem.pdf` con el enunciado
- [ ] Agregar la letra al loop del script (`for dir in A B C ... K;`)
- [ ] Ejecutar el script desde Linux

---

## 9. Solución de Problemas Comunes

| Problema | Causa | Solución |
|----------|-------|----------|
| Problemas no visibles para equipos | `allow_submit` está en false | Verificar `domjudge-problem.ini` tiene `allow_submit = 1`, o activar manualmente desde admin |
| No se detectan testcases | ZIPs creados en Windows con backslash | Generar ZIPs en Linux con el script |
| Script no ejecuta en Linux | Terminaciones de línea Windows (CRLF) | `sed -i 's/\r$//' script.sh` |
| No se suben jury solutions | Admin sin equipo asociado | Asociar un equipo al usuario admin |
| Colores no aparecen en scoreboard | Falta `color` en `domjudge-problem.ini` | Agregar `color = #HEXCODE` al .ini |
| `zip: command not found` | zip no instalado | `apt install zip -y` |

---

## 10. Notas Importantes

- **Siempre generar los ZIPs en Linux**, nunca en Windows. Los ZIPs de Windows usan backslash en las rutas y DOMjudge no los reconoce correctamente.
- El **nombre del ZIP** (sin extensión) se usa como identificador corto del problema en el scoreboard.
- Si re-subes un ZIP con el mismo nombre, DOMjudge **actualiza** el problema existente (no crea duplicado).
- Si subes un ZIP con nombre nuevo, DOMjudge **crea** un problema nuevo.
- Antes de re-subir problemas, es recomendable borrarlos desde el panel admin para evitar conflictos.
