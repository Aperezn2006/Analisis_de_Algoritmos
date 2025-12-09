/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}


PDICT init_dictionary(int size, char order) {
    PDICT d;

    if (size <= 0) return NULL;
    if (order != SORTED && order != NOT_SORTED) return NULL;

    d = (PDICT)malloc(sizeof(DICT));
    if (!d) return NULL;

    d->table = (int *)malloc(sizeof(int) * size);
    if (!d->table) {
        free(d);
        return NULL;
    }

    d->size = size;    
    d->n_data = 0;     
    d->order = order;  

    return d;
}


/*
 * free_dictionary:
 * Frees all memory reserved by the dictionary ADT routines.
 */
void free_dictionary(PDICT pdict) {
    if (!pdict) return;

    free(pdict->table);
    pdict->table = NULL;

    free(pdict);
}

/*
 * insert_dictionary:
 * Inserts a key into the dictionary according to its order type.
 *
 * Assumed return convention :
 *   0  -> OK
 *  -1  -> ERROR
 * Change these values if your assignment defines different constants.
 */
int insert_dictionary(PDICT pdict, int key) {
    int j, U;
    int A;

    if (!pdict || !pdict->table) return -1;
    if (pdict->n_data >= pdict->size) return -1;

    /* Unsorted table: insert at the end */
    if (pdict->order == NOT_SORTED) {
        pdict->table[pdict->n_data] = key;
        pdict->n_data++;
        return 0;
    }

    /*
     * Sorted table:
     * 1) Place the new element at the end
     * 2) Reposition it using a single insertion-sort pass
     */
    U = pdict->n_data;
    pdict->table[U] = key;

    A = pdict->table[U];
    j = U - 1;

    while (j >= 0 && pdict->table[j] > A) {
        pdict->table[j + 1] = pdict->table[j];
        j--;
    }
    pdict->table[j + 1] = A;

    pdict->n_data++;
    return 0;
}

/*
 * massive_insertion_dictionary:
 * Inserts the n_keys keys from the array 'keys' into the dictionary
 * by performing n_keys successive calls to insert_dictionary.
 *
 * Assumed return convention:
 *   0  -> all keys inserted successfully
 *  -1  -> ERROR (if any insertion fails or invalid arguments)
 * Adjust if your assignment specifies a different behavior.
 */
int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys) {
    int i;

    if (!pdict || !keys || n_keys < 0) return -1;

    for (i = 0; i < n_keys; i++) {
        if (insert_dictionary(pdict, keys[i]) == -1) {
            return -1;
        }
    }

    return 0;
}

/*
 * search_dictionary:
 * Searches for 'key' in the dictionary using the search routine
 * indicated by 'method'.
 *
 * The function returns the position of the key in the table through *ppos.
 *
 * Assumed return convention (common in labs):
 *  - Returns ERROR on invalid arguments.
 *  - Otherwise returns whatever 'method' returns (e.g., FOUND / NOT_FOUND).
 *
 * If the dictionary is empty, *ppos is set to -1 and NOT_FOUND is returned.
 */
int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method) {
    int F, L;

    if (!pdict || !pdict->table || !ppos || !method) return ERR;

    if (pdict->n_data == 0) {
        *ppos = -1;
        return NOT_FOUND;
    }

    F = 0;
    L = pdict->n_data - 1;

    return method(pdict->table, F, L, key, ppos);
}


/*
 * These search routines implement:
 *  - binary search
 *  - linear search
 *  - self-organizing linear search (swap with previous when found)
 *
 * They must place in *ppos:
 *  - the position of the key if found
 *  - NOT_FOUND if the key is not in the table
 *
 * Assumption (very common in these labs):
 *  - The return value is the number of comparisons performed.
 * If your assignment instead expects a status code (FOUND/NOT_FOUND),
 * you can change the returns easily and keep the same *ppos behavior.
 */

int lin_search(int *table, int F, int L, int key, int *ppos) {
    int i;
    int comps = 0;

    if (!table || !ppos || F > L) {
        if (ppos) *ppos = NOT_FOUND;
        return ERR;
    }

    for (i = F; i <= L; i++) {
        comps++;
        if (table[i] == key) {
            *ppos = i;
            return comps;
        }
    }

    *ppos = NOT_FOUND;
    return comps;
}

int lin_auto_search(int *table, int F, int L, int key, int *ppos) {
    int i;
    int comps = 0;

    if (!table || !ppos || F > L) {
        if (ppos) *ppos = NOT_FOUND;
        return ERR;
    }

    for (i = F; i <= L; i++) {
        comps++;
        if (table[i] == key) {
            /* If it is not already at the first position, swap with previous */
            if (i > F) {
                int tmp = table[i - 1];
                table[i - 1] = table[i];
                table[i] = tmp;
                *ppos = i - 1; /* new position after swap */
            } else {
                *ppos = i;
            }
            return comps;
        }
    }

    *ppos = NOT_FOUND;
    return comps;
}


int bin_search(int *table, int F, int L, int key, int *ppos) {
    int low, high, mid;
    int comps = 0;

    if (!table || !ppos || F > L) {
        if (ppos) *ppos = NOT_FOUND;
        return ERR;
    }

    low = F;
    high = L;

    while (low <= high) {
        mid = low + (high - low) / 2;

        comps++;
        if (table[mid] == key) {
            *ppos = mid;
            return comps;
        }

        comps++;
        if (table[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    *ppos = NOT_FOUND;
    return comps;
}

