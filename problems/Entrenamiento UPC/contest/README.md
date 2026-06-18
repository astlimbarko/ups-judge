# Archivos de Importación - Formato JSON/YAML

## Orden de importación (IMPORTANTE)

Importar en este orden desde Jury → Import/Export → Importar JSON/YAML:

1. **groups.json** → Tipo: groups
2. **organizations.json** → Tipo: organizations
3. **teams.json** → Tipo: teams
4. **accounts.yaml** → Tipo: accounts

## Equipos

| Usuario | Contraseña | Equipo | Universidad |
|---------|------------|--------|-------------|
| team01 | byteforce | ByteForce | UTEPSA |
| team02 | nullpointers | NullPointers | UTEPSA |
| team03 | stackoverflow | StackOverflow | UDABOL |
| team04 | runtimeterror | Runtime Terror | UDABOL |
| team05 | segfault | Segfault | EMI |
| team06 | ctrl+cctrl+v | Ctrl+C Ctrl+V | EMI |

## Notas
- El username es siempre `teamXX` (estándar DOMjudge)
- La contraseña es el nombre del equipo en minúscula sin espacios
- Primero importar groups, luego organizations, luego teams, luego accounts
- Si se importa en otro orden dará error de referencia
