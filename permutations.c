/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: ismael Nevado Serrano, Arturo Perez Noves
 * Version: 1.1
 * Fecha: 15-10-2025
 *
 */

#include "permutations.h"
#include <stdlib.h>

/***************************************************/
/* Function: random_num Date:                      */
/* Authors: ismael Nevado Serrano, Arturo Perez Noves*/
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
int random_num(int inf, int sup)
{
  return rand() / (RAND_MAX + 1.) * (sup - inf + 1) + inf;
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors: ismael Nevado Serrano, Arturo Perez Noves */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation n>0*/
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int *generate_perm(int N)
{
  int *perm;
  int j, temp, r;

  perm = malloc(N * sizeof(int));
  if (!perm)
    return NULL;

  for (j = 0; j < N; j++)
    perm[j] = j + 1;

  for (j = 0; j < N; j++)
  {
    r = random_num(j, N - 1);
    temp = perm[j];
    perm[j] = perm[r];
    perm[r] = temp;
  }
  return perm;
}

/****************************************************/
/* Function: generate_permutations Date:            */
/* Authors: ismael Nevado Serrano, Arturo Perez Noves*/
/*                                                  */
/* Function that generates n_perms random           */
/* permutations with N elements                     */
/*                                                  */
/* Input:                                           */
/* int n_perms: Number of permutations  n_perms>0   */
/* int N: Number of elements in each permutation N>0*/
/* Output:                                          */
/* int**: Array of pointers to integer that point   */
/* to each of the permutations                      */
/* NULL en case of error                            */
/***************************************************/
int **generate_permutations(int n_perms, int N)
{
  int **perms;
  int i;

  perms = (int **)malloc(n_perms * sizeof(int *));
  if (!perms)
    return NULL;

  for (i = 0; i < n_perms; i++)
  {

    perms[i] = generate_perm(N);

    if (perms[i] == NULL)
    {

      for (i--; i >= 0; i--)
        free(perms[i]);
      free(perms);
      return NULL;
    }
  }
  return perms;
}
