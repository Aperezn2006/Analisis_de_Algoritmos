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
int InsertSort(int* array, int ip, int iu)
{
  
}


/***************************************************/
/* Function: SelectSort    Date:                   */
/* No funciona para arrays vacios                  */
/***************************************************/
int BubbleSort(int* array, int ip, int iu){
  int i, j, OB;

  for (i = ip; i < iu ; i++){
    for (j = 0; j < (iu - i); j++){
      int temp;
      if (array[j] > array[j+1]){
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
        OB++;
      };
    }
  }
  return OB;
}






