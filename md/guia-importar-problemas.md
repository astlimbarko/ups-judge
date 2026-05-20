# 📚 HardKoder - Guía para Importar Problemas

**Fecha**: Diciembre 21, 2025  
**Estado**: ✅ HELLO IMPORTADO EXITOSAMENTE - Otros 2 ZIPs listos

---

## 🎯 PROBLEMAS DISPONIBLES

### **Problemas de Ejemplo Incluidos:**
1. **A - Hello** (`hello`)
   - **Color**: Púrpura (`#9486EA`)
   - **Descripción**: Problema básico "Hello World"
   - **Tiempo límite**: 5 segundos

2. **B - Fltcmp** (`fltcmp`)
   - **Color**: Rojo (`#E93603`)
   - **Descripción**: Comparación de números flotantes
   - **Tiempo límite**: 5 segundos

3. **C - Boolfind** (`boolfind`)
   - **Color**: Marrón (`#9B630C`)
   - **Descripción**: Búsqueda booleana
   - **Tiempo límite**: 5 segundos

---

## 📁 ARCHIVOS PREPARADOS

### **Archivos ZIP Individuales:**
```
HardKoder/domjudge-9.0.0/example_problems/hello.zip     - ✅ IMPORTADO (ID: p1)
HardKoder/domjudge-9.0.0/example_problems/fltcmp.zip    - 🔄 LISTO PARA IMPORTAR  
HardKoder/domjudge-9.0.0/example_problems/boolfind.zip  - 🔄 LISTO PARA IMPORTAR
```

**Cada archivo contiene:**
- ✅ Problema completo con casos de prueba
- ✅ Múltiples soluciones de ejemplo (correctas e incorrectas)
- ✅ Archivo `problem.yaml` con configuración
- ✅ PDF con enunciado del problema
- ✅ Validadores personalizados (cuando aplique)
- ✅ **FORMATO CORRECTO**: `problem.yaml` en la raíz del ZIP

---

## 🚀 PASOS PARA IMPORTAR (Interfaz Web)

### **Método Correcto: Importación Individual**

#### **1. Acceder al Panel de Administración**
```
URL: http://localhost:12345/login
Usuario: admin
Contraseña: Fro1k-1HYeB-B_lz
```

#### **2. Ir a Import/Export**
- En el menú superior, ir a **"Import and export"**
- O ir directamente a: http://localhost:12345/jury/import-export

#### **3. Importar Cada Problema**
En la sección **"Problems"** → **"Import archive"**:

**Paso 1: Importar Hello (Problema A)**
- Seleccionar archivo: `hello.zip`
- Hacer clic en **"Import"**
- Verificar que aparezca mensaje de éxito

**Paso 2: Importar Fltcmp (Problema B)**
- Seleccionar archivo: `fltcmp.zip`
- Hacer clic en **"Import"**
- Verificar que aparezca mensaje de éxito

**Paso 3: Importar Boolfind (Problema C)**
- Seleccionar archivo: `boolfind.zip`
- Hacer clic en **"Import"**
- Verificar que aparezca mensaje de éxito

#### **4. Verificar Importación**
- Ir a: http://localhost:12345/jury/problems
- Deberías ver los 3 problemas listados

---

## 🔧 MÉTODO ALTERNATIVO (Línea de Comandos)

### **Si la interfaz web no funciona:**

#### **1. Copiar archivo al contenedor**
```bash
cd HardKoder/domjudge-9.0.0
docker compose cp example_problems.zip domjudge:/tmp/
```

#### **2. Ejecutar importación**
```bash
docker compose exec domjudge php /home/chalo/Documentos/Kodra/HardKoder/domjudge-9.0.0/webapp/bin/console domjudge:import-contest /tmp/example_problems.zip
```

---

## 📋 VERIFICACIÓN POST-IMPORTACIÓN

### **1. Verificar Problemas**
- Ir a: http://localhost:12345/jury/problems
- Deberías ver los 3 problemas listados

### **2. Verificar Scoreboard Público**
- Ir a: http://localhost:12345/public
- Los problemas deberían aparecer en el header

### **3. Verificar Problemset**
- Ir a: http://localhost:12345/public/problems
- Deberías ver la lista de problemas con colores

---

## 🎨 RESULTADO ESPERADO

### **Scoreboard con Problemas:**
```
Rank | Team | Score | A | B | C |
-----|------|-------|---|---|---|
  1  | ...  |  ...  |🟣 |🔴 |🟤 |
```

### **Colores por Problema:**
- **A (Hello)**: Púrpura `#9486EA`
- **B (Fltcmp)**: Rojo `#E93603`
- **C (Boolfind)**: Marrón `#9B630C`

---

## 🚨 TROUBLESHOOTING

### **Si no aparecen los problemas:**

#### **1. Verificar Contest Activo**
- Ir a: http://localhost:12345/jury/contests
- Asegurarse de que hay un contest activo
- Si no hay, crear uno nuevo

#### **2. Verificar Configuración**
- Los problemas deben estar asociados a un contest
- El contest debe estar en estado "started" o "running"

#### **3. Logs de Error**
```bash
docker compose logs domjudge | grep -i error
```

---

## 🎯 PRÓXIMO PASO

### **Una vez importados los problemas:**
1. ✅ Verificar que aparecen en el scoreboard
2. ✅ Probar acceso a problemset público
3. ✅ **Comenzar personalización HardKoder** del scoreboard con datos reales

**¡Con problemas reales podremos ver mejor cómo se ve el diseño oscuro elegante!**

---

**Última actualización**: Diciembre 21, 2025 - 02:45 AM