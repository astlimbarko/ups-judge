#!/bin/bash
# Script para GENERAR ZIPs y SUBIR problemas a DOMjudge
# Ejecutar desde Ubuntu Server en la carpeta donde estan las carpetas A, B, C...

API_URL="http://192.168.42.130/api/v4"
CID="Warm-up_UPC"
USER="admin"
PASS="CTtxu9vA5Rh35h8-"

# Carpeta donde se generaran los ZIPs
ZIP_DIR="./zips"
mkdir -p "$ZIP_DIR"

echo "========================================="
echo " Generando ZIPs y subiendo a DOMjudge"
echo " Contest: $CID"
echo " Server: $API_URL"
echo "========================================="
echo ""

# Verificar conexion
echo "Verificando conexion..."
RESPONSE=$(curl -s -o /dev/null -w "%{http_code}" -u "$USER:$PASS" "$API_URL/contests/$CID")
if [ "$RESPONSE" != "200" ]; then
    echo "ERROR: No se pudo conectar al contest. HTTP code: $RESPONSE"
    echo "Verifica que el contest '$CID' existe y las credenciales son correctas."
    exit 1
fi
echo "Conexion OK!"
echo ""

# Generar ZIPs desde las carpetas de problemas (A, B, C, D, E)
echo "--- Generando ZIPs ---"
for dir in A B C D E; do
    if [ -d "$dir" ]; then
        rm -f "$ZIP_DIR/$dir.zip"
        cd "$dir"
        zip -r "../$ZIP_DIR/$dir.zip" . -x ".*"
        cd ..
        echo "  Generado: $dir.zip"
    else
        echo "  ADVERTENCIA: Carpeta '$dir' no encontrada, saltando."
    fi
done
echo ""

# Subir cada ZIP
echo "--- Subiendo problemas ---"
for zip in "$ZIP_DIR"/*.zip; do
    FILENAME=$(basename "$zip")
    echo "Subiendo: $FILENAME"
    RESULT=$(curl -s -u "$USER:$PASS" -F "zip=@$zip" "$API_URL/contests/$CID/problems")
    echo "  Respuesta: $RESULT"
    echo ""
done

echo "========================================="
echo " Listo! Problemas generados y subidos."
echo "========================================="
