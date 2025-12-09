/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Ismael Nevado Serrano, Arturo Perez Noves
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "sorting.h"

/***************************************************/
/* Function: InsertSort    Date:    15/10/2025
  *  Sorts an array using the Insertion Sort algorithm.
  *  The function takes an array and its bounds as input and sorts the array in place.
  *  It returns the number of operations performed.
  *
  * @param int* array Pointer to the array to be sorted. array!=NULL
  * @param int ip    Lower index of the array segment to be sorted. ip>=0
  * @param int iu    Upper index of the array segment to be sorted. iu>ip
  *
  * @return Number of operations performed during sorting.
  */
int InsertSort(int *array, int ip, int iu)
{
  int count_OB = 0, i, j;

  for ( i = ip; i < iu; i++)
  {
    
    for ( j = i; j > 0 && array[j - 1] > array[j]; j--)
    {
      int aux = array[j];
      array[j] = array[j - 1];
      array[j - 1] = aux;
      count_OB++;
    }
    
    
  }

  return count_OB;
}




/* Function: SelectSort    Date: 15/10/2025       
* Sorts an array using the Selection Sort        
* algorithm. The function takes an array and its  
* bounds as input and sorts the array in place.  
* It returns the number of operations performed.
*                                                 *
* @param int* array Pointer to the array to be sorted.  array!=NULL
* @param int ip    Lower index of the array segment to be sorted. ip>=0
* @param int iu    Upper index of the array segment to be sorted. iu>ip 
*                                                 *
* @return Number of operations performed during sorting.
*/
int BubbleSort(int *array, int ip, int iu)
{
  int count_OB = 0, i, j;

  for ( i = ip; i < iu; i++)
  {
    
    for ( j = ip; j < iu - (i - ip); j++)
    {
      if (array[j] > array[j + 1])
      {
        int aux = array[j];
        array[j] = array[j + 1];
        array[j + 1] = aux;
      }
      count_OB++;
    }
    
  }

  return count_OB;
}

/*
  function merge: merges two sorted halves of an array.
  It takes the array and the indices defining the two halves.
  It returns the number of operations performed during the merge.

  arguments:
    int *tabla: pointer to the array to be merged. tabla!=NULL
    int ip: lower index of the first half. ip>=0
    int iu: upper index of the second half. iu>ip
    int imedio: upper index of the first half. ip<=imedio<iu

  returns:
    Number of operations performed during the merge.

*/
int merge(int *tabla, int ip, int iu, int imedio) {

    const int n_left  = imedio - ip + 1;
    const int n_right = iu - imedio;

    int i = 0;   
    int t = 0;            
    int j = 0;               
    int k = ip;              
    int ops = 0;       

    int *tmp = (int *)malloc((size_t)(n_left + n_right) * sizeof(int));
    if (tmp == NULL) return ERR;

          
    
    for (t = 0; t < n_left; ++t) {
        tmp[t] = tabla[ip + t];
        ++ops;               
    }
    for (t = 0; t < n_right; ++t) {
        tmp[n_left + t] = tabla[imedio + 1 + t];
        ++ops;               
    }

    
    while (i < n_left && j < n_right) {
        ++ops; 
        if (tmp[i] <= tmp[n_left + j]) {
            tabla[k++] = tmp[i++];
            ++ops; 
        } else {
            tabla[k++] = tmp[n_left + j++];
            ++ops; 
        }
    }
    
    while (i < n_left) {
        tabla[k++] = tmp[i++];
        ++ops; 
    }
    while (j < n_right) {
        tabla[k++] = tmp[n_left + j++];
        ++ops; 
    }

    free(tmp);
    return ops;
}

/* 
  funcion mergesort: sorts an array using the Mergesort algorithm.
  It takes the array and its bounds as input and sorts the array in place.
  It returns the number of operations performed during sorting.

  argument:
    int *tabla: pointer to the array to be sorted. tabla!=NULL
    int ip: lower index of the array segment to be sorted. ip>=0
    int iu: upper index of the array segment to be sorted. iu>ip

  returns:
    Number of operations performed during sorting.
  
 */

int mergesort(int *tabla, int ip, int iu) {

    int ops_left, ops_right, ops_merge;
    int mid;

    if (ip >= iu) return 0;

    mid = ip + (iu - ip) / 2;

    ops_left = mergesort(tabla, ip, mid);
    if (ops_left == ERR) return ERR;

    ops_right = mergesort(tabla, mid + 1, iu);
    if (ops_right == ERR) return ERR;

    ops_merge = merge(tabla, ip, iu, mid);
    if (ops_merge == ERR) return ERR;

    return ops_left + ops_right + ops_merge;
}



/* 
  funcion median: selects the first element as pivot.
  It takes the array and the indices defining the segment.
  It returns the number of operations performed during the selection.

  arguments:
    int *tabla: pointer to the array. tabla!=NULL
    int ip: lower index of the array segment. ip>=0
    int iu: upper index of the array segment. iu>ip
    int *pos: pointer to store the position of the median. pos!=NULL

  returns:
    Number of operations performed during median selection.
*/
int median(int *tabla, int ip, int iu, int *pos) {
    *pos = ip;
    return 0;
}
/* 
  funcion median_avg: selects the average of the first and last elements as pivot.
  It takes the array and the indices defining the segment.
  It returns the number of operations performed during the selection.

  arguments:
    int *tabla: pointer to the array. tabla!=NULL
    int ip: lower index of the array segment. ip>=0
    int iu: upper index of the array segment. iu>ip
    int *pos: pointer to store the position of the median. pos!=NULL

  returns:
    Number of operations performed during median selection.
*/
int median_avg(int *tabla, int ip, int iu, int *pos) {
    if (!tabla || !pos || ip < 0 || iu < ip) return ERR;
    *pos = (ip + iu) / 2;
    return 0;                /* 0 OBs extra */
}

/*
  funcion median_stat: selects the median of the first, middle, and last elements as pivot.
  It takes the array and the indices defining the segment.
  It returns the number of operations performed during the selection.

  arguments:
    int *tabla: pointer to the array. tabla!=NULL
    int ip: lower index of the array segment. ip>=0
    int iu: upper index of the array segment. iu>ip
    int *pos: pointer to store the position of the median. pos!=NULL

  returns:
    Number of operations performed during median selection. 
*/
int median_stat(int *tabla, int ip, int iu, int *pos) {

    int mid = (ip + iu) / 2;
    int i = ip, j = mid, k = iu;
    int tt, t;

    int a = tabla[i], b = tabla[j], c = tabla[k];
 
    if (a > b) { t=i; i=j; j=t; tt=a; a=b; b=tt; }
   
    if (b > c) { t=j; j=k; k=t; tt=b; b=c; c=tt; }
 
    if (a > b) { t=i; i=j; j=t; }

    *pos = j;
    return 3; 
}

/*
  funcion partition: partitions an array segment around a pivot.
  It takes the array and the indices defining the segment.
  It returns the number of operations performed during partitioning.

  arguments:
    int *tabla: pointer to the array to be partitioned. tabla!=NULL
    int ip: lower index of the array segment to be partitioned. ip>=0
    int iu: upper index of the array segment to be partitioned. iu>ip
    int *pos: pointer to store the final position of the pivot. pos!=NULL

  returns:
    Number of operations performed during partitioning.
*/
int partition(int *tabla, int ip, int iu, int *pos) {

    long ops = 0;
    int pivpos;
    int r, pivot, i, j, t;

    r = median(tabla, ip, iu, &pivpos);
    if (r == ERR) return ERR;
    ops += r;                 

    if (pivpos != ip) {t = tabla[ip]; tabla[ip] = tabla[pivpos]; tabla[pivpos] = t; ops += 3; }

    pivot = tabla[ip]; ops++;
    i = ip;            ops++;

    for (j = ip + 1; j <= iu; ++j) {
        ops++;                         
        if (tabla[j] < pivot) { ops++; 
            ++i; ops++;
            t = tabla[i]; tabla[i] = tabla[j]; tabla[j] = t; ops += 3;
        }
    }

    
    {t = tabla[ip]; tabla[ip] = tabla[i]; tabla[i] = t; ops += 3; }
    *pos = i;

    if (ops > INT_MAX) ops = INT_MAX;
    return (int)ops;
}


/* 
  funcion quicksort: sorts an array using the Quicksort algorithm.
  It takes the array and its bounds as input and sorts the array in place.
  It returns the number of operations performed during sorting.

  argument:
    int *tabla: pointer to the array to be sorted. tabla!=NULL
    int ip: lower index of the array segment to be sorted. ip>=0
    int iu: upper index of the array segment to be sorted. iu>ip

  returns:
    Number of operations performed during sorting.
  
 */
int quicksort(int *tabla, int ip, int iu) {
    
    int pos, r, ops = 0;
    if (ip >= iu) return 0;

    r = partition(tabla, ip, iu, &pos); if (r == ERR) return ERR; ops += r;

    r = quicksort(tabla, ip, pos - 1); if (r == ERR) return ERR; ops += r;
    r = quicksort(tabla, pos + 1, iu); if (r == ERR) return ERR; ops += r;

    return ops;
}
