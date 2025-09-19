#!/bin/bash
# filepath: /home/arthur/Documents/Analisis_de_Algoritmos-main/count_numbers.sh

# Archivo de salida del big test
OUTPUT_FILE="e1_big_test.txt"

# Verifica si el archivo existe
if [[ ! -f "$OUTPUT_FILE" ]]; then
  echo "El archivo $OUTPUT_FILE no existe."
  exit 1
fi

# Cuenta las ocurrencias de cada número y las ordena
echo "Contando números en $OUTPUT_FILE..."
sort -n "$OUTPUT_FILE" | uniq -c | sort -k2n > number_counts.txt

echo "Conteo completado. Los resultados se han guardado en number_counts.txt."