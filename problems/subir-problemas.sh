#!/bin/bash
# Script para subir todos los problemas al contest via API
# Ejecutar desde Ubuntu Server donde corre DOMjudge

API_URL="http://192.168.42.130/api/v4"
CID="testing-ups-2026"
USER="admin"
PASS="5Vzz6HPmTMFD7ZP0"

# Carpeta donde estan los ZIPs
ZIP_DIR="./zips"

echo "========================================="
echo " Subiendo problemas a DOMjudge"
echo " Contest: $CID"
echo " Server: $API_URL"
echo "========================================="
echo ""

# Primero verificar conexion
echo "Verificando conexion..."
RESPONSE=$(curl -s -o /dev/null -w "%{http_code}" -u "$USER:$PASS" "$API_URL/contests/$CID")
if [ "$RESPONSE" != "200" ]; then
    echo "ERROR: No se pudo conectar al contest. HTTP code: $RESPONSE"
    echo "Verifica que el contest '$CID' existe y las credenciales son correctas."
    exit 1
fi
echo "Conexion OK!"
echo ""

# Subir cada ZIP
for zip in "$ZIP_DIR"/*.zip; do
    FILENAME=$(basename "$zip")
    echo "Subiendo: $FILENAME"
    RESULT=$(curl -s -u "$USER:$PASS" -F "zip=@$zip" "$API_URL/contests/$CID/problems")
    echo "  Respuesta: $RESULT"
    echo ""
done

echo "========================================="
echo " Listo! Todos los problemas subidos."
echo "========================================="
