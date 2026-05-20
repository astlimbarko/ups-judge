# Guía: Importar Concursos en DOMjudge

## Formato de Archivo

DOMjudge acepta archivos **JSON** o **YAML** para importar concursos. El formato sigue la especificación ICPC Contest API.

---

## Estructura del archivo YAML (recomendado)

```yaml
id: mi-concurso-2025
name: "Concurso de Programación UPC 2025"
short_name: "UPC2025"
start_time: "2025-06-15T09:00:00-04:00"
duration: "5:00:00"
scoreboard_freeze_duration: "1:00:00"
penalty_time: 20
```

### Campos explicados:

| Campo | Descripción | Ejemplo |
|-------|-------------|---------|
| `id` | Identificador único (sin espacios) | `upc-2025` |
| `name` | Nombre completo del concurso | `"Concurso UPC 2025"` |
| `short_name` | Nombre corto | `"UPC2025"` |
| `start_time` | Fecha/hora de inicio (ISO 8601 con zona horaria) | `"2025-06-15T09:00:00-04:00"` |
| `duration` | Duración total (H:MM:SS) | `"5:00:00"` |
| `scoreboard_freeze_duration` | Tiempo antes del final para congelar marcador | `"1:00:00"` |
| `penalty_time` | Minutos de penalización por intento incorrecto | `20` |

---

## Estructura del archivo JSON

```json
{
  "id": "mi-concurso-2025",
  "name": "Concurso de Programación UPC 2025",
  "short_name": "UPC2025",
  "start_time": "2025-06-15T09:00:00-04:00",
  "duration": "5:00:00",
  "scoreboard_freeze_duration": "1:00:00",
  "penalty_time": 20
}
```

---

## Zona Horaria Bolivia

Para Bolivia (GMT-4), usa el sufijo `-04:00` en las fechas:
```
"start_time": "2025-06-15T09:00:00-04:00"
```

---

## Ejemplo: Concurso de entrenamiento (sin hora fija)

Si quieres un concurso que esté siempre activo para práctica:

```yaml
id: training-permanente
name: "Entrenamiento Permanente"
short_name: "TRAIN"
start_time: "2025-01-01T00:00:00-04:00"
duration: "8760:00:00"
penalty_time: 20
```

(8760 horas = 1 año)

---

## Ejemplo: Concurso de 3 horas con congelamiento

```yaml
id: final-upc-2025
name: "Final Programming Championship UPC 2025"
short_name: "FINAL2025"
start_time: "2025-07-20T14:00:00-04:00"
duration: "3:00:00"
scoreboard_freeze_duration: "0:30:00"
penalty_time: 20
```

---

## Cómo importar

1. Ve a `/jury` → **Importar / exportar**
2. En la sección "Concursos", haz clic en **Importar JSON / YAML**
3. Selecciona tu archivo `.yaml` o `.json`
4. Haz clic en importar

---

## Notas importantes

- El `id` debe ser único — si ya existe un concurso con ese id, se actualizará
- Las horas usan formato ISO 8601 con zona horaria
- La duración usa formato `H:MM:SS` o `HH:MM:SS`
- `scoreboard_freeze_duration` es opcional
- `penalty_time` es opcional (por defecto 20 minutos)
- Si `start_time` es null, el concurso queda en estado "pendiente" hasta que lo actives manualmente

---

## Campos opcionales adicionales

```yaml
activate_time: "2025-06-14T09:00:00-04:00"   # Cuándo se activa (visible para equipos)
deactivate_time: "2025-06-16T09:00:00-04:00"  # Cuándo se desactiva
```

- `activate_time`: momento en que el concurso se vuelve visible para los equipos (puede ser antes del start)
- `deactivate_time`: momento en que el concurso desaparece de la vista
