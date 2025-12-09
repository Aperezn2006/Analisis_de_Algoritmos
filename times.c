/**
 *
 * Description: Implementation of time measurement functions
 *
 * File: times.c
 * Author: ismael Nevado Serrano, Arturo Perez Noves
 * Version: 1.0
 * Date: 15-10-2025
 *
 */

#include <stdio.h>
#include "times.h"
#include <stdlib.h>
#include <time.h>
#include "sorting.h"
#include "permutations.h"

/************************************************************************************************/
/* Function: average_sorting_time Date: 15/10/2025                                              */
/*                                                                                              */
/*  Calculates the average sorting time and number                                              */
/* of operations for a given sorting method over                                                */
/* multiple random permutations.                                                                */
/*                                                                                              */
/* Parameters:                                                                                  */
/*   pfunc_sort metodo  - Pointer to the sorting function. metodo!=NULL                         */
/*   int n_perms        - Number of permutations to test. n_perms>0                             */
/*   int N              - Size of each permutation. N>0                                         */
/*   PTIME_AA ptime     - Pointer to PTIME_AA struct where results will be stored. ptime!=NULL  */
/*                                                                                              */
/* Returns:                                                                                     */
/*   OK on success, ERR on error                                                                */
/*                                                                                              */
/* Side effects:                                                                                */
/*   Updates the fields of the PTIME_AA struct                                                  */
/*   with timing and operation statistics.                                                      */
/************************************************************************************************/
short average_sorting_time(pfunc_sort metodo, int n_perms, int N, PTIME_AA ptime)
{

  int i, count_OB = 0, temp_OB=0, start = 0, end = 0;
  int *array;
  double total;


  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->min_ob = __INT_MAX__;
  ptime->max_ob = 0;

  start = clock();
  for (i = 0; i < n_perms; i++)
  {
    array = generate_perm(N);
    if (array == NULL)
      return ERR;

    temp_OB = metodo(array, 0, N - 1);
    free(array);
    if (temp_OB < 0)
      return ERR;

    if (temp_OB < ptime->min_ob)
    {
      ptime->min_ob = temp_OB;
    }

    if (temp_OB > ptime->max_ob)
    {
      ptime->max_ob = temp_OB;
    }

    count_OB += temp_OB;
  }
  end = clock();

  total = (double)(end - start) / (double)CLOCKS_PER_SEC; /* seg totales */
  ptime->time = total / (double)n_perms;                  /* seg por perm */

  ptime->time = total;

  ptime->average_ob = (double)count_OB / n_perms;

  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date: 15/10/2025

 * @brief Generates timing/operation statistics for a sorting method over a
 *        range of input sizes and writes them to a text file.
 *
 * For each size n in [num_min, num_max] with step incr, it runs the given
 * sorting method on n_perms permutations and uses average_sorting_time()
 * to compute the average running time and operation counts (mean, min, max).
 * It writes one line per size to the output file 'file'.
 *
 * @param pfunc_sort method   Pointer to the sorting function to benchmark. method!=NULL
 * @param char* file     Path to the output file. It will be created or overwritten. file!=NULL
 * @param int num_min  Minimum permutation size (>= 1).
 * @param int num_max  Maximum permutation size (>= num_min).
 * @param int incr     Step between consecutive sizes (> 0).
 * @param int n_perms  Number of permutations per size for averaging (> 0).
 *
 * @return OK on success; ERR if any error occurs (file open failure, memory
 *         allocation failure, invalid parameters, or an error from
 *         average_sorting_time()).
 *
 * @post Output format (one line per size):
 *       "<n> <avg_time> <avg_ob> <min_ob> <max_ob>"
 *       Values are space-separated; floating-point values use a decimal point.
 *
 * @warning Ensure that num_max >= num_min and incr > 0. Close the file and
 *          free allocated memory on error paths.
 */

short generate_sorting_times(pfunc_sort method, char *file, int num_min, int num_max, int incr, int n_perms)
{

  int i, n;
  double time;
  FILE *f;
  PTIME_AA ptime;

  f = fopen(file, "w");
  if (f == NULL)
    return ERR;

  n = (num_max - num_min) / incr + 1;

  ptime = calloc(n, sizeof(TIME_AA));
  if (ptime == NULL)
  {
    fclose(f);
    return ERR;
  }

  for (i = 0; i < n; i++)
  {
     int size = num_min + i * incr; /* size of permutation */
    printf("Calculating time for size %d - %d\n", size, num_max );
   

    time = average_sorting_time(method, n_perms, size, &ptime[i]);
    if (time == ERR)
    {
      free(ptime);
      fclose(f);
      return ERR;
    }
  }

  for (i = 0; i < n; i++)
  {
    fprintf(f, "%f %f %d %d\n", ptime[i].time, ptime[i].average_ob, ptime[i].min_ob, ptime[i].max_ob);
  }
  fclose(f);
  save_time_table("time_table_insert.txt", ptime, n);

  free(ptime);
  return OK;
}

/***************************************************/
/* Function: save_time_table Date: 15/10/2025
 *
 * @brief Writes a table of timing/operation statistics to a text file.
 *
 * Each element of the array `ptime` produces one line in the output file,
 * containing: time, average_ob, min_ob, and max_ob, separated by spaces.
 *
 * @param char* file     Path to the output file (created or overwritten). file!=NULL
 * @param PTIME_AA ptime Pointer to an array of TIME_AA entries to write. ptime!=NULL
 * @param int n_times    Number of elements in `ptime` to write (>= 0).
 *
 * @return OK on success; ERR if the file cannot be opened.
 *
 * @note This function performs no memory allocation and closes the file
 *       before returning. Time complexity is O(n_times) for I/O.
 */
short save_time_table(char *file, PTIME_AA ptime, int n_times)
{

  int i;
  FILE *f;

  f = fopen(file, "w");
  if (f == NULL)
    return ERR;

  fprintf(f, "# N  n_elems  time  average_ob  min_ob  max_ob\n");

  for (i = 0; i < n_times; i++)
  {
    fprintf(f, "%d %d %.10f %f %d %d\n", ptime[i].N, ptime[i].n_elems, ptime[i].time, ptime[i].average_ob, ptime[i].min_ob, ptime[i].max_ob);
  }

  fclose(f);
  return OK;
}


