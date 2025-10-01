/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "sorting.h"

/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/
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




/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
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
        count_OB++;
      }
    }
    
  }

  return count_OB;
}
