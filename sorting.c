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
