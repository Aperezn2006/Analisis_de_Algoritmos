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


#endif
