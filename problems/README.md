# Contest Test - UPS Judge

## Problemas incluidos (orden del contest)

| Letra | Carpeta | Problema | Samples | Secrets |
|-------|---------|----------|---------|---------|
| A | hola-mundo-v2 | Hola Mundo | 1 | 3 |
| B | echo | Echo | 1 | 3 |
| C | suma-simple-v2 | Suma Simple | 1 | 4 |
| D | doble-numero | Doble del Número | 1 | 3 |
| E | area-rectangulo | Área de Rectángulo | 1 | 3 |
| F | par-impar | Par o Impar | 2 | 3 |
| G | mayor-de-dos | Mayor de Dos Números | 1 | 3 |
| H | contador | Contador | 1 | 3 |
| I | tabla-multiplicar | Tabla de Multiplicar | 1 | 3 |
| J | nombre-completo | Nombre Completo | 1 | 3 |

## Estado

- [x] Carpetas de problemas creadas
- [x] problem.yaml en cada problema
- [x] data/sample/ y data/secret/ con casos de prueba
- [x] submissions/accepted/ con soluciones en C++ y Python
- [x] enunciado.html en cada problema (para convertir a PDF)
- [x] Line endings Unix (LF)
- [ ] **PENDIENTE**: Convertir enunciado.html → problem.pdf (lo hace el usuario)
- [ ] **PENDIENTE**: Crear ZIPs (se hará después de tener los PDFs)

## Instrucciones para completar

### 1. Convertir HTML a PDF
Abrir cada `enunciado.html` en Chrome → Imprimir → Guardar como PDF.
Guardar como `problem.pdf` dentro de la misma carpeta del problema.

### 2. Crear ZIPs (cuando los PDFs estén listos)
Avisar a Kiro para que genere los ZIPs con forward slashes.

### 3. Importar en DOMjudge
Jury → Problems → seleccionar contest → Upload cada ZIP individual.

## Soluciones incluidas
Cada problema tiene solución en:
- C++ (`solucion.cpp`)
- Python (`solucion.py`)
