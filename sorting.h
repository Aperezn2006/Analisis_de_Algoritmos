/**
 *
 * Descripcion: Header file for sorting functions 
 *
 * Fichero: sorting.h
 * Autor: ismael Nevado Serrano, Arturo Perez Noves
 * Version: 1.0
 * Fecha: 15-10-2025
 *
 */

#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

/* type definitions */
typedef int (* pfunc_sort)(int*, int, int);


/* Functions */

int BubbleSort(int* array, int ip, int iu);
int InsertSort(int* array, int ip, int iu);

/**
 * @brief Ordena in-place el subarray tabla[ip..iu] con MergeSort.
 *
 * @param tabla   Puntero al primer elemento del array.
 * @param ip      Índice inicial (inclusive).
 * @param iu      Índice final   (inclusive).
 * @return Número de operaciones básicas (comparaciones + escrituras) o SORT_ERR.
 */
int mergesort(int *tabla, int ip, int iu);
/**
 * @brief Mezcla las dos mitades ordenadas de tabla[ip..iu].
 *
 * @param tabla    Puntero al primer elemento del array.
 * @param ip       Índice inicial (inclusive).
 * @param iu       Índice final   (inclusive).
 * @param imedio   Índice medio que separa las dos mitades.
 * @return Número de operaciones básicas (comparaciones + escrituras) o SORT_ERR.
 */
int merge(int* tabla, int ip, int iu, int imedio);

int quicksort(int* tabla, int ip, int iu);

int partition(int* tabla, int ip, int iu,int *pos);
int median(int *tabla, int ip, int iu,int *pos);
int median_avg(int *tabla, int ip, int iu, int *pos);
int median_stat (int *tabla, int ip, int iu, int *pos);


#endif
