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

int MergeSort (int* tabla, int ip, int iu){
  int imedio;

  if (ip > iu) return ERR;

  if (ip == iu) return OK; /*CONDICION DE PARADA*/

  imedio = (ip + iu) / 2;

  MergeSort (tabla, ip, imedio - 1);

  MergeSort (tabla, imedio, iu);

  merge (tabla, ip, iu, imedio);

}


int merge(int* tabla, int ip, int iu, int imedio){

  int itres, i = ip, j = imedio;
  int* tabla_resultante = NULL;

  tabla_resultante = (int *) malloc ((iu-ip + 1) * sizeof(int));

  if (tabla_resultante == NULL) return ERR;

  for (itres = 0; i <= imedio || j <= iu; itres++){
    if (tabla[i] < tabla[j]){
      tabla_resultante[itres] = tabla[i];
      i++;
    } else {
      tabla_resultante[itres] = tabla[j];
      j++;
    }
  }
  if (i <= imedio){
    while (j <= iu)
    {
      tabla_resultante[itres]=tabla[j];
      itres++;
      j++;
    } 
  } else {
    while (i<=imedio){
      tabla_resultante[itres]=tabla[i];
      itres++;
      i++;
    }
  }
  
  return OK;
}

int quicksort(int* tabla, int ip, int iu){
  int pos, ob = 0;

  if (ip >= iu) return 0;

  ob += median (tabla, ip, iu, &pos);
  ob += partition (tabla, ip, iu, &pos);
  ob += quicksort(tabla, ip, pos - 1);
  ob += quicksort(tabla, pos + 1, iu);

  return ob;
}

int partition(int* tabla, int ip, int iu, int *pos){
  int i, aux, j;
  int ob = 0;
  int piv = tabla[*pos];


  aux = tabla[ip];
  tabla[ip] = tabla[*pos];
  tabla[*pos] = aux;
  ob += 3;

  i = ip + 1;

  for (j = ip + 1; j <= iu; j++){
    ob++;
    if (tabla[j] < piv){
      aux = tabla[i];
      tabla[i] = tabla[j];
      tabla[j] = aux;
      i++;
      ob += 3;
    }
    ob++;
  }
  
  aux = tabla[ip];
  tabla[ip] = tabla[i-1];
  tabla[i-1] = aux;
  ob += 3; 

  *pos = i - 1;

  return ob;
}

int median(int *tabla, int ip, int iu,int *pos){
  int ob = 0;

  *pos = ip;
  ob++;

  return ob;
}

int median_avg(int *tabla, int ip, int iu, int *pos){
  int ob = 0;
  
  pos = (iu - ip) / 2;
  ob++;

  return ob;
}


int median_stat (int *tabla, int ip, int iu, int *pos){
  int ob = 0;

  return ob;
}
