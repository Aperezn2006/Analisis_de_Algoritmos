#include <stdlib.h>
#include <time.h>

#include "times.h"
#include "search.h"
#include "permutations.h"

short average_search_time(pfunc_search method,
                          pfunc_key_generator generator,
                          char order,
                          int N,
                          int n_times,
                          PTIME_AA ptime)
{
  int i, pos;
  int count_OB = 0, temp_OB = 0;
  clock_t start, end;

  int *perm = NULL;
  int *keys = NULL;
  int n_total;
  double total;

  PDICT pdict = NULL;

  if (!method || !generator || !ptime) return ERR;
  if (N <= 0 || n_times <= 0) return ERR;

  ptime->N = N;
  ptime->n_elems = N * n_times;
  ptime->min_ob = __INT_MAX__;
  ptime->max_ob = 0;

  pdict = init_dictionary(N, order);
  if (!pdict) return ERR;

  perm = generate_perm(N);
  if (!perm) {
    free_dictionary(pdict);
    return ERR;
  }

  if (massive_insertion_dictionary(pdict, perm, N) == ERR) {
    free(perm);
    free_dictionary(pdict);
    return ERR;
  }

  n_total = N * n_times;
  keys = (int *)malloc(sizeof(int) * n_total);
  if (!keys) {
    free(perm);
    free_dictionary(pdict);
    return ERR;
  }

  /* Use the provided generator */
    uniform_key_generator(keys, n_total, N) ;

  start = clock();
  for (i = 0; i < n_total; i++) {

    temp_OB = search_dictionary(pdict, keys[i], &pos, method);
    if (temp_OB < 0) {
      free(keys);
      free(perm);
      free_dictionary(pdict);
      return ERR;
    }

    if (temp_OB < ptime->min_ob) ptime->min_ob = temp_OB;
    if (temp_OB > ptime->max_ob) ptime->max_ob = temp_OB;

    count_OB += temp_OB;
  }
  end = clock();

  total = (double)(end - start) / (double)CLOCKS_PER_SEC;
  ptime->time = total;
  ptime->average_ob = (double)count_OB / (double)n_total;

  free(keys);
  free(perm);
  free_dictionary(pdict);

  return OK;
}

short generate_search_times(pfunc_search method,
                            pfunc_key_generator generator,
                            int order,
                            char* file,
                            int num_min,
                            int num_max,
                            int incr,
                            int n_times)
{
  int i, n;
  PTIME_AA ptime;

  if (!method || !generator || !file) return ERR;
  if (num_min <= 0 || num_max < num_min || incr <= 0 || n_times <= 0) return ERR;

  /* number of different sizes to test */
  n = (num_max - num_min) / incr + 1;

  ptime = (PTIME_AA)calloc(n, sizeof(TIME_AA));
  if (!ptime) return ERR;

  for (i = 0; i < n; i++) {
    int size = num_min + i * incr;

    printf("Calculating time for size %d - %d\n", size, num_max);

    if (average_search_time(method, generator, (char)order, size, n_times, &ptime[i]) == ERR) {
      free(ptime);
      return ERR;
    }
  }

  /* Required by statement */
  if (save_time_table(file, ptime, n) == ERR) {
    free(ptime);
    return ERR;
  }

  free(ptime);
  return OK;
}
