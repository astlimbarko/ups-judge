# 🎯 HardKoder - Guía para Crear Problemas Propios

**Fecha**: Diciembre 21, 2025  
**Estado**: ✅ Guía actualizada con lecciones aprendidas - PROBADA Y FUNCIONANDO

---

## � **LEUCCIÓN CRÍTICA APRENDIDA**

### **⚠️ NOMBRE DEL PDF ES CRUCIAL:**
```yaml
✅ CORRECTO: problem.pdf    # DOMjudge lo reconoce como enunciado
❌ ERROR: suma-simple.pdf   # Solo muestra botón "Samples"
❌ ERROR: enunciado.pdf     # Solo muestra botón "Samples"
❌ ERROR: mi-problema.pdf   # Solo muestra botón "Samples"
```

### **🎯 RESULTADO SEGÚN EL NOMBRE:**
- **Con `problem.pdf`**: Los usuarios ven el enunciado completo + botón Samples
- **Sin `problem.pdf`**: Los usuarios SOLO ven botón Samples (casos de prueba)

---

## 📋 ESTRUCTURA BÁSICA DE UN PROBLEMA

### **Archivos Obligatorios:**
```
mi-problema/
├── problem.yaml          # ✅ OBLIGATORIO - Configuración del problema
├── problem.pdf           # ✅ OBLIGATORIO - DEBE llamarse "problem.pdf" exactamente
├── data/                 # ✅ OBLIGATORIO - Casos de prueba
│   ├── sample/           # Casos de muestra (visibles para usuarios)
│   │   ├── 1.in         # Entrada del caso 1
│   │   ├── 1.ans        # Salida esperada del caso 1
│   │   ├── 2.in         # Entrada del caso 2
│   │   └── 2.ans        # Salida esperada del caso 2
│   └── secret/           # Casos secretos (ocultos, para evaluación)
│       ├── 1.in
│       ├── 1.ans
│       ├── 2.in
│       ├── 2.ans
│       └── ...
├── submissions/          # 🔄 OPCIONAL - Soluciones de ejemplo
│   ├── accepted/         # Soluciones correctas
│   ├── wrong_answer/     # Soluciones incorrectas
│   ├── time_limit_exceeded/
│   └── run_time_error/
└── .timelimit           # 🔄 OPCIONAL - Tiempo límite personalizado
```

---

## 📝 ARCHIVO `problem.yaml`

### **Configuración Básica:**
```yaml
# Nombre del problema (aparece en la interfaz)
name: "Mi Problema Increíble"

# ID externo (usado internamente, sin espacios)
# external_id: mi-problema-increible

# Límites del problema
limits:
  time: 2.0          # Tiempo en segundos (opcional)
  memory: 512        # Memoria en MB (opcional)
  output: 8          # Límite de salida en MB (opcional)

# Configuración de validación
validation: default   # o 'custom' si tienes validador propio

# Tipo de problema
type: pass-fail      # o 'scoring' para problemas con puntuación parcial

# Configuración de colores (opcional)
rgb: '#FF5733'       # Color hexadecimal para el problema
```

### **Ejemplo Completo:**
```yaml
name: "Suma de Dos Números"
external_id: suma-dos-numeros
limits:
  time: 1.0
  memory: 256
  output: 4
validation: default
type: pass-fail
rgb: '#2E8B57'
```

---

## 📄 CREAR EL ENUNCIADO (problem.pdf)

### **🚨 REGLA CRÍTICA:**
```yaml
El archivo DEBE llamarse exactamente: problem.pdf
❌ NO usar: suma-simple.pdf, enunciado.pdf, mi-problema.pdf
✅ USAR: problem.pdf
```

### **Opciones para crear el PDF:**

#### **Opción 1: Usar LaTeX (Recomendado)**
```latex
\documentclass{article}
\usepackage[utf8]{inputenc}
\usepackage[spanish]{babel}

\title{Suma de Dos Números}
\author{HardKoder}
\date{}

\begin{document}
\maketitle

\section{Descripción}
Dados dos números enteros A y B, calcular su suma.

\section{Entrada}
Una línea con dos enteros A y B separados por un espacio.
Restricciones: $-10^9 \leq A, B \leq 10^9$

\section{Salida}
Un entero que representa A + B.

\section{Ejemplo}
\textbf{Entrada:}
\begin{verbatim}
3 5
\end{verbatim}

\textbf{Salida:}
\begin{verbatim}
8
\end{verbatim}

\end{document}
```

#### **Opción 2: Usar Word/Google Docs**
1. Crear documento con las secciones:
   - **Título del problema**
   - **Descripción**
   - **Entrada** (formato y restricciones)
   - **Salida** (formato esperado)
   - **Ejemplos** (al menos 1)
2. Exportar como PDF

#### **Opción 3: Usar Markdown + Pandoc**
```bash
# Crear archivo problema.md y convertir
pandoc problema.md -o problem.pdf
```

---

## 🧪 CREAR CASOS DE PRUEBA

### **Casos de Muestra (data/sample/)**
**Visibles para los participantes**

#### **Archivo: `data/sample/1.in`**
```
3 5
```

#### **Archivo: `data/sample/1.ans`**
```
8
```

### **Casos Secretos (data/secret/)**
**Ocultos, usados para evaluación final**

#### **Ejemplo de casos secretos:**
```bash
# data/secret/1.in
1000000000 1000000000

# data/secret/1.ans
2000000000

# data/secret/2.in
-500 300

# data/secret/2.ans
-200

# data/secret/3.in
0 0

# data/secret/3.ans
0
```

### **Consejos para Casos de Prueba:**
- **Casos límite**: Valores mínimos y máximos
- **Casos especiales**: Ceros, negativos, etc.
- **Casos normales**: Valores típicos
- **Al menos 5-10 casos secretos** para buena cobertura

---

## 💻 SOLUCIONES DE EJEMPLO (Opcional)

### **Solución Correcta (submissions/accepted/)**

#### **Archivo: `submissions/accepted/solucion.cpp`**
```cpp
#include <iostream>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;
    cout << a + b << endl;
    return 0;
}
```

#### **Archivo: `submissions/accepted/solucion.py`**
```python
a, b = map(int, input().split())
print(a + b)
```

### **Soluciones Incorrectas (submissions/wrong_answer/)**

#### **Archivo: `submissions/wrong_answer/multiplicacion.cpp`**
```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    cout << a * b << endl;  // Error: multiplica en vez de sumar
    return 0;
}
```

---

## ⏱️ CONFIGURAR TIEMPO LÍMITE

### **Archivo: `.timelimit`**
```
2
```
*Tiempo en segundos (entero)*

### **O usar problem.yaml:**
```yaml
limits:
  time: 2.0  # Tiempo en segundos (decimal)
```

---

## 📦 CREAR EL ARCHIVO ZIP

### **🚨 PASOS CRÍTICOS:**

#### **Paso 1: Verificar nombres de archivos**
```bash
# ANTES de crear ZIP, verificar:
ls mi-problema/
# Debe mostrar:
# problem.yaml  ✅
# problem.pdf   ✅ (NO suma-simple.pdf)
# data/         ✅
# submissions/  ✅ (opcional)
```

#### **Paso 2: Organizar archivos**
```bash
mi-problema/
├── problem.yaml          # ✅ Configuración
├── problem.pdf           # ✅ NOMBRE EXACTO
├── data/
│   ├── sample/
│   │   ├── 1.in
│   │   └── 1.ans
│   └── secret/
│       ├── 1.in
│       ├── 1.ans
│       ├── 2.in
│       └── 2.ans
└── submissions/
    └── accepted/
        └── solucion.cpp
```

#### **Paso 3: Crear ZIP CORRECTAMENTE**
```bash
# Desde DENTRO de la carpeta del problema
cd mi-problema
zip -r ../mi-problema.zip .

# ✅ Verificar que problem.yaml esté en la raíz del ZIP
unzip -l ../mi-problema.zip | grep problem.yaml

# ✅ Verificar que problem.pdf esté en la raíz del ZIP  
unzip -l ../mi-problema.zip | grep problem.pdf
```

---

## 🚀 IMPORTAR TU PROBLEMA

### **Paso 1: Subir ZIP**
1. Ir a: http://localhost:12345/jury/import-export
2. Sección "Problems" → "Import archive"
3. Seleccionar tu archivo `mi-problema.zip`
4. Hacer clic en "Import"

### **Paso 2: Verificar Importación**
1. Ir a: http://localhost:12345/jury/problems
2. Buscar tu problema en la lista
3. Hacer clic para ver detalles

### **Paso 3: Vincular a Contest**
1. Ir a: http://localhost:12345/jury/contests
2. Editar el contest activo
3. Agregar tu problema a la lista

---

## 🎨 EJEMPLO COMPLETO: "Suma Simple" (PROBADO Y FUNCIONANDO)

### **📁 Estructura de archivos REAL que funcionó:**
```
suma-simple/
├── problem.yaml          # ✅ Configuración
├── problem.pdf           # ✅ NOMBRE EXACTO (no suma-simple.pdf)
├── .timelimit           # ✅ Tiempo límite: 1 segundo
├── data/
│   ├── sample/          # ✅ 2 casos de muestra
│   │   ├── 1.in         # "3 5"
│   │   ├── 1.ans        # "8"
│   │   ├── 2.in         # "-10 15"
│   │   └── 2.ans        # "5"
│   └── secret/          # ✅ 3 casos secretos
│       ├── 1.in         # "0 0"
│       ├── 1.ans        # "0"
│       ├── 2.in         # "1000 -1000"
│       ├── 2.ans        # "0"
│       ├── 3.in         # "-500 300"
│       └── 3.ans        # "-200"
└── submissions/         # ✅ Soluciones de ejemplo
    ├── accepted/
    │   ├── solucion.cpp # Solución C++ correcta
    │   └── solucion.py  # Solución Python correcta
    └── wrong_answer/
        └── multiplicacion.cpp # Solución incorrecta (multiplica)
```

### **📋 Archivo problem.yaml REAL:**
```yaml
name: "Suma Simple"
external_id: suma-simple
limits:
  time: 1.0
  memory: 256
  output: 4
validation: default
type: pass-fail
rgb: '#2E8B57'
```

### **💻 Solución C++ REAL que funcionó:**
```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
    return 0;
}
```

### **🎯 Resultado de Importación EXITOSA:**
```
✅ Problem "Suma Simple" imported successfully
✅ Added/updated problem statement from: problem.pdf
✅ Added/updated 2 sample testcase(s): {1,2}.{in,ans}
✅ Added/updated 3 secret testcase(s): {1,2,3}.{in,ans}
✅ Added 3 jury solution(s)
✅ Problem ID: p4
✅ Vinculado al contest: training2025
✅ PDF visible para usuarios ✅
✅ Botón "Samples" disponible ✅
```

---

## 🎨 EJEMPLO COMPLETO: "Suma de Dos Números"

### **Estructura de archivos:**
```
suma-dos-numeros/
├── problem.yaml
├── problem.pdf
├── data/
│   ├── sample/
│   │   ├── 1.in          # "3 5"
│   │   └── 1.ans         # "8"
│   └── secret/
│       ├── 1.in          # "1000000000 1000000000"
│       ├── 1.ans         # "2000000000"
│       ├── 2.in          # "-500 300"
│       ├── 2.ans         # "-200"
│       ├── 3.in          # "0 0"
│       └── 3.ans         # "0"
└── submissions/
    ├── accepted/
    │   ├── solucion.cpp
    │   └── solucion.py
    └── wrong_answer/
        └── multiplicacion.cpp
```

---

## 🔧 HERRAMIENTAS ÚTILES

### **Para generar casos de prueba:**
```python
# generador.py
import random

for i in range(1, 11):  # 10 casos
    a = random.randint(-1000000000, 1000000000)
    b = random.randint(-1000000000, 1000000000)
    
    with open(f'secret/{i}.in', 'w') as f:
        f.write(f'{a} {b}\n')
    
    with open(f'secret/{i}.ans', 'w') as f:
        f.write(f'{a + b}\n')
```

### **Para validar casos:**
```bash
# Probar solución contra casos
for caso in data/secret/*.in; do
    echo "Probando $caso"
    ./solucion < $caso > salida.tmp
    diff salida.tmp ${caso%.in}.ans
done
```

---

## 🚨 ERRORES COMUNES Y SOLUCIONES

### **❌ Error: "ZIP file contains neither domjudge-problem.ini nor problem.yaml"**
- **Causa**: `problem.yaml` no está en la raíz del ZIP
- **Solución**: Crear ZIP desde DENTRO de la carpeta del problema

### **❌ Error: "No testcases found"**
- **Causa**: Falta carpeta `data/` o archivos `.in/.ans`
- **Solución**: Verificar estructura de carpetas

### **❌ Error: "Invalid YAML"**
- **Causa**: Sintaxis incorrecta en `problem.yaml`
- **Solución**: Verificar indentación y formato YAML

### **❌ Error: Solo aparece botón "Samples", no se ve el PDF**
- **Causa**: El PDF NO se llama `problem.pdf`
- **Solución**: Renombrar a `problem.pdf` exactamente
- **Ejemplo**: `suma-simple.pdf` → `problem.pdf`

### **❌ Error: "Missing fields: duration" (en contests)**
- **Causa**: Falta campo `duration` en YAML de contest
- **Solución**: Agregar `duration: "8760:00:00"` para 365 días

---

## 🎯 CONSEJOS PARA BUENOS PROBLEMAS

### **Diseño del Problema:**
1. **Enunciado claro**: Sin ambigüedades
2. **Ejemplos suficientes**: Al menos 2-3 casos de muestra
3. **Restricciones claras**: Límites de entrada bien definidos
4. **Dificultad apropiada**: Acorde al nivel de la competencia

### **Casos de Prueba:**
1. **Cobertura completa**: Probar todos los casos límite
2. **Casos especiales**: Valores mínimos, máximos, ceros
3. **Casos normales**: Valores típicos del problema
4. **Suficientes casos**: 10-20 casos secretos mínimo

### **Soluciones:**
1. **Múltiples lenguajes**: C++, Python, Java
2. **Soluciones incorrectas**: Para probar el sistema
3. **Optimización**: Solución debe pasar en el tiempo límite

---

**¡Con esta guía puedes crear problemas profesionales para HardKoder!**

---

**🎉 GUÍA PROBADA Y FUNCIONANDO - Ejemplo "Suma Simple" importado exitosamente**

---

**Última actualización**: Diciembre 21, 2025 - 04:00 AM