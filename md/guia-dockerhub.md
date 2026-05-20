# Guía: Empaquetar y Subir a Docker Hub

## Objetivo

Subir la imagen personalizada de DOMjudge (con todas las modificaciones de UPC) a Docker Hub para que en cualquier VPS se pueda descargar con un solo comando.

**Usuario Docker Hub:** astlimbark
**Imagen final:** `astlimbark/domjudge-utepsa`

---

## Requisitos previos

- Docker instalado en tu máquina
- Cuenta en Docker Hub (ya la tienes: astlimbark)
- La imagen construida localmente y funcionando

---

## Paso 1: Login en Docker Hub

```bash
docker login
```

Te pedirá usuario y contraseña de Docker Hub (astlimbark).

---

## Paso 2: Construir la imagen con el tag correcto

Desde la carpeta del proyecto:

```bash
cd ~/Documentos/Kodra/HardKoder/domjudge-9.0.0
docker build -t astlimbark/domjudge-utepsa:latest .
```

Esto construye la imagen y la etiqueta con tu usuario de Docker Hub.

---

## Paso 3: Verificar que la imagen existe

```bash
docker images | grep domjudge-utepsa
```

Deberías ver algo como:
```
astlimbark/domjudge-utepsa   latest   abc123def456   2 minutes ago   1.5GB
```

---

## Paso 4: Subir (push) a Docker Hub

```bash
docker push astlimbark/domjudge-utepsa:latest
```

Esto sube la imagen. Puede tardar varios minutos dependiendo de tu conexión (la imagen pesa ~1-2GB).

---

## Paso 5: Verificar en Docker Hub

Ve a: https://hub.docker.com/r/astlimbark/domjudge-utepsa

Ahí debería aparecer tu imagen publicada.

---

## Cómo usar en un VPS (despliegue)

### Opción A: Solo el contenedor DOMjudge

En tu VPS, crea un archivo `docker-compose.yml`:

```yaml
services:
  mariadb:
    image: mariadb
    environment:
      - MYSQL_ROOT_PASSWORD=domjudge
      - MYSQL_USER=domjudge
      - MYSQL_PASSWORD=domjudge
      - MYSQL_DATABASE=domjudge
    ports:
      - 127.0.0.1:13306:3306
    command: --max-connections=1000 --max-allowed-packet=512M --innodb_snapshot_isolation=OFF
    volumes:
      - db_data:/var/lib/mysql

  domjudge:
    image: astlimbark/domjudge-utepsa:latest
    hostname: domjudge-upc
    ports:
      - 80:80
    privileged: true
    cgroup: host
    volumes:
      - /sys/fs/cgroup:/sys/fs/cgroup
      - /chroot
    environment:
      - TZ=America/La_Paz
    depends_on:
      - mariadb

volumes:
  db_data:
```

### Desplegar:

```bash
docker compose up -d
```

Y listo. Tu servidor estará en `http://tu-ip-del-vps/`

---

## Actualizar la imagen

Cuando hagas cambios y quieras actualizar:

```bash
# En tu máquina local
cd ~/Documentos/Kodra/HardKoder/domjudge-9.0.0
docker build -t astlimbark/domjudge-utepsa:latest .
docker push astlimbark/domjudge-utepsa:latest

# En el VPS
docker compose pull
docker compose up -d
```

---

## Versionado (opcional)

Puedes crear versiones específicas:

```bash
docker build -t astlimbark/domjudge-utepsa:v1.0 .
docker push astlimbark/domjudge-utepsa:v1.0
```

Así puedes tener `latest` (última) y versiones fijas por si necesitas volver atrás.

---

## Importante: El Dockerfile actual

Tu Dockerfile actual solo instala Java sobre la imagen base. Para que la imagen incluya TODAS tus personalizaciones (templates, CSS, logos), necesitas un Dockerfile más completo que copie tus archivos modificados dentro de la imagen.

### Dockerfile mejorado para producción:

```dockerfile
FROM docker.io/domjudge/domjudge-contributor

USER root

# Instalar Java
RUN mkdir -p /var/lib/apt/lists/partial && \
    apt-get update && \
    apt-get install -y --no-install-recommends default-jdk && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Copiar templates personalizados
COPY webapp/templates/ /opt/domjudge/domserver/webapp/templates/

# Copiar CSS personalizado
COPY webapp/public/style_domjudge.css /opt/domjudge/domserver/webapp/public/style_domjudge.css

# Copiar imágenes personalizadas (logos)
COPY webapp/public/images/upc_logo.png /opt/domjudge/domserver/webapp/public/images/upc_logo.png
COPY webapp/public/images/upc_logo_gris.png /opt/domjudge/domserver/webapp/public/images/upc_logo_gris.png
COPY webapp/public/images/lab_sistemas_logo.png /opt/domjudge/domserver/webapp/public/images/lab_sistemas_logo.png

USER domjudge
```

**Nota:** La ruta dentro del contenedor puede variar. Para verificar la ruta correcta:
```bash
docker exec -it domjudge-900-domjudge-1 find / -name "style_domjudge.css" 2>/dev/null
```

Usa esa ruta en los COPY del Dockerfile.

---

## Resumen de comandos

```bash
# Construir
docker build -t astlimbark/domjudge-utepsa:latest .

# Login
docker login

# Subir
docker push astlimbark/domjudge-utepsa:latest

# En VPS: descargar y correr
docker pull astlimbark/domjudge-utepsa:latest
docker compose up -d
```

---

## Notas

- La primera vez que subes tarda bastante (1-2GB de imagen)
- Las siguientes veces solo sube las capas que cambiaron (mucho más rápido)
- La imagen es pública por defecto en Docker Hub (cualquiera puede descargarla)
- Si quieres privada, configúralo en Docker Hub settings
