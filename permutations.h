/**
 *
 * Descripcion: Header for functions for permutations generation
 *
 * Fichero: permutations.h
 * Autor: ismael Nevado Serrano, Arturo Perez Noves
 * Version: 1.1
 * Fecha: 15-10-2025
 *
 */

#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

/* constants */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

int random_num(int inf, int sup);
int* generate_perm(int N);
int** generate_permutations(int n_perms, int N);

#endif
