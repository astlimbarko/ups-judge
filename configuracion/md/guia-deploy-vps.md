# Deploy UPS-Judge en VPS (Ubuntu Server)

## Requisitos

- Ubuntu Server 22.04+ con Docker y Docker Compose instalados
- cgroups v2 habilitados (verificar: `cat /sys/fs/cgroup/cgroup.controllers`)
- Puerto 80 abierto

## Primer deploy (desde cero)

```bash
git clone https://github.com/astlimbarko/ups-judge.git
cd ups-judge
sudo docker compose up -d
```

Esperar ~30 segundos a que el domserver instale la BD.

## Paso obligatorio: sincronizar password del judgehost

El domserver genera una password aleatoria para el usuario `judgehost`.
El judgehost necesita esa misma password para conectarse a la API.

```bash
# 1. Ver la password que genero el domserver
sudo docker exec ups-judge-app cat /opt/domjudge/domserver/etc/restapi.secret
```

La salida es algo como:
```
default http://localhost/ judgehost XXXXXXXXXXXXXX
```

La 4ta columna (XXXXXXXXXXXXXX) es la password.

```bash
# 2. Editar docker-compose.yml y poner esa password en JUDGEDAEMON_PASSWORD
nano docker-compose.yml
# Cambiar: JUDGEDAEMON_PASSWORD=UpsJudgeHost2025
# Por:     JUDGEDAEMON_PASSWORD=XXXXXXXXXXXXXX (la que leiste)

# 3. Reiniciar solo el judgehost
sudo docker compose restart judgehost
```

Alternativa: cambiar la password desde la web:
- Ir a /jury → Usuarios → judgehost → Editar
- Cambiar password a `UpsJudgeHost2025` (la que esta en el docker-compose)
- Reiniciar judgehost: `sudo docker compose restart judgehost`

## Ver password de admin

```bash
sudo docker exec ups-judge-app cat /opt/domjudge/domserver/etc/initial_admin_password.secret
```

## Resetear password de admin

```bash
sudo docker exec ups-judge-app /opt/domjudge/domserver/webapp/bin/console domjudge:reset-user-password admin
```

## Verificar que todo funciona

```bash
# Ver estado de contenedores
sudo docker compose ps

# Logs del domserver
sudo docker logs ups-judge-app

# Logs del judgehost (debe decir "No submissions in queue")
sudo docker logs ups-judge-judgehost

# Si el judgehost dice "401 Unauthorized" → la password no coincide (ver paso anterior)
```

## Acceso web

- Scoreboard: http://TU_IP/
- Login: http://TU_IP/login
- Admin: http://TU_IP/jury

## Actualizar imagen despues de cambios

```bash
cd ups-judge
sudo docker compose pull
sudo docker compose up -d
```

## Reiniciar sin perder datos

```bash
sudo docker compose restart
```

Los volumenes `mariadb_data` y `domjudge_etc` persisten la BD y los secrets entre reinicios.

## Reinstalar desde cero (borra TODO)

```bash
sudo docker compose down -v
sudo docker compose up -d
```

El `-v` borra los volumenes (BD + secrets). Se regenera todo.

## Problemas comunes

### "cgroup: host" da error
Tu kernel no tiene cgroups v2. Verificar:
```bash
cat /sys/fs/cgroup/cgroup.controllers
# Si no existe, agregar a /etc/default/grub:
# GRUB_CMDLINE_LINUX="systemd.unified_cgroup_hierarchy=1"
# Luego: sudo update-grub && sudo reboot
```

### Judgehost dice "401 Unauthorized"
La password no coincide. Seguir el paso "sincronizar password del judgehost".

### Password de admin cambia en cada reinicio
Asegurate de tener el volumen `domjudge_etc` en el docker-compose.
Sin ese volumen, los secrets se regeneran en cada reinicio.

### El judgehost no juzga (no pasa de "pending")
Verificar que el judgehost esta conectado:
- Ir a /jury → Jueces → debe aparecer "judgedaemon-0" activo
- Si no aparece, revisar logs: `sudo docker logs ups-judge-judgehost`
