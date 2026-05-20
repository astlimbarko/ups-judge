# Guía: Importar Equipos y Grupos en DOMjudge

## Conceptos Clave

En DOMjudge hay 3 cosas diferentes:

| Concepto | Qué es | Ejemplo |
|----------|--------|---------|
| **Groups** (Categorías) | Clasificación de equipos | "Participantes", "Observadores" |
| **Teams** (Equipos) | Los equipos que compiten | "Los Hackers", "Byte Force" |
| **Accounts** (Cuentas) | Login y contraseña para cada equipo | usuario: team01, pass: abc123 |

Se importan por separado. Primero groups, luego teams, luego accounts.

---

## Formato TSV (separado por tabulaciones)

Los archivos TSV usan TAB como separador (no espacios ni comas).

---

## 1. Archivo groups.tsv (Categorías)

Define las categorías/grupos de equipos.

### Formato:
```
groups	1
ID	Nombre
```

### Ejemplo (groups.tsv):
```
groups	1
1	Participantes
2	Observadores
3	Organizadores
```

- Primera línea: `groups` + TAB + `1` (versión del formato)
- Siguientes líneas: `ID` + TAB + `Nombre del grupo`

---

## 2. Archivo teams.tsv (Equipos)

Define los equipos y a qué grupo pertenecen.

### Formato:
```
teams	1
ID_equipo	ID_externo	ID_grupo	Nombre_equipo	Nombre_universidad	Nombre_corto_universidad	País
```

### Ejemplo (teams.tsv):
```
teams	1
1	team01	1	Los Hackers	UPC	UPC	BOL
2	team02	1	Byte Force	UPC	UPC	BOL
3	team03	1	Code Warriors	UPC	UPC	BOL
4	team04	2	Observador 1	UPC	UPC	BOL
```

- Primera línea: `teams` + TAB + `1`
- Columnas separadas por TAB:
  1. ID del equipo (número)
  2. ID externo (puede ser igual al ID o un código)
  3. ID del grupo al que pertenece (debe existir en groups.tsv)
  4. Nombre del equipo
  5. Nombre de la universidad/afiliación
  6. Nombre corto de la universidad
  7. Código de país (3 letras ISO, ej: BOL, ARG, PER)

---

## 3. Archivo accounts.tsv (Cuentas de usuario)

Define las credenciales de login para cada equipo.

### Formato:
```
accounts	1
Tipo	Nombre_completo	Usuario	Contraseña
```

### Ejemplo (accounts.tsv):
```
accounts	1
team	Los Hackers	team01	password123
team	Byte Force	team02	password456
team	Code Warriors	team03	password789
```

- Primera línea: `accounts` + TAB + `1`
- Columnas separadas por TAB:
  1. Tipo: `team` (para equipos), `judge` (para jueces), `admin`
  2. Nombre completo (debe coincidir con el nombre del equipo)
  3. Nombre de usuario (login)
  4. Contraseña

---

## Orden de importación

1. Primero: **groups.tsv** (crea las categorías)
2. Segundo: **teams.tsv** (crea los equipos asignados a categorías)
3. Tercero: **accounts.tsv** (crea las cuentas de login)

---

## Cómo importar

1. Ve a `/jury` → **Importar / exportar**
2. En la sección "Equipos y grupos", selecciona el tipo (groups, teams, o accounts)
3. Selecciona tu archivo `.tsv`
4. Haz clic en importar

---

## Ejemplo completo para 10 equipos

### groups.tsv:
```
groups	1
1	Participantes
```

### teams.tsv:
```
teams	1
1	team01	1	Equipo Alpha	UPC	UPC	BOL
2	team02	1	Equipo Beta	UPC	UPC	BOL
3	team03	1	Equipo Gamma	UPC	UPC	BOL
4	team04	1	Equipo Delta	UPC	UPC	BOL
5	team05	1	Equipo Epsilon	UPC	UPC	BOL
6	team06	1	Equipo Zeta	UPC	UPC	BOL
7	team07	1	Equipo Eta	UPC	UPC	BOL
8	team08	1	Equipo Theta	UPC	UPC	BOL
9	team09	1	Equipo Iota	UPC	UPC	BOL
10	team10	1	Equipo Kappa	UPC	UPC	BOL
```

### accounts.tsv:
```
accounts	1
team	Equipo Alpha	team01	upc2025alpha
team	Equipo Beta	team02	upc2025beta
team	Equipo Gamma	team03	upc2025gamma
team	Equipo Delta	team04	upc2025delta
team	Equipo Epsilon	team05	upc2025epsilon
team	Equipo Zeta	team06	upc2025zeta
team	Equipo Eta	team07	upc2025eta
team	Equipo Theta	team08	upc2025theta
team	Equipo Iota	team09	upc2025iota
team	Equipo Kappa	team10	upc2025kappa
```

---

## Notas importantes

- Los archivos DEBEN usar TAB real como separador (no espacios)
- La primera línea es el encabezado con el tipo y versión
- Los IDs de grupo en teams.tsv deben existir previamente (importar groups primero)
- El nombre en accounts.tsv debe coincidir exactamente con el nombre del equipo en teams.tsv
- Si un equipo ya existe con ese ID, se actualiza en vez de crear uno nuevo

---

## Acceso público al scoreboard

Cualquier persona puede ver el marcador sin login en:
```
http://localhost:12345/public
```

No necesita cuenta ni contraseña. Solo abre esa URL en el navegador.
