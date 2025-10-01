/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include <stdlib.h>

/***************************************************/
/* Function: random_num Date:                      */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup){
  return rand()/(RAND_MAX+1.)*(sup-inf+1)+inf;
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N){
  int j, temp, r;
  int* perm = (int *)malloc (N * sizeof(int));

  if (!perm) return NULL;

  for (j=0; j<N; j++)
    perm [j] = j+1;
  
  for (j=0; j<N; j++){
    r = random_num(j, N-1);
    temp = perm[j];
    perm[j] = perm[r];
    perm[r] = temp;
  }
  return perm; 
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N){
  int** perms = NULL;
  int i;

  perms = (int **) malloc (n_perms * sizeof(int*));
  if (perms == NULL) return NULL;

  for (i = 0; i < n_perms; i++){
    perms[i] = generate_perm(N);
    if (perms[i] == NULL){
      
      for (i--; i >= 0; i--)
        free(perms[i]);
      free(perms);
      return NULL;
    }
  }
  return perms;
}
