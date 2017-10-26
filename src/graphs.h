#ifndef GRAPHS_H
# define GRAPHS_H

# include <stdio.h>
# include "array.h"
# include "stack.h"
# include "control.h"

/* DEAD CODE */
/* enum g_type */
/*   { */
/*     CHAR = 0, */
/*     INT = 1 */
/*   }; */

/* int (*)(int x, int y, struct graph *g)[2] = */
/* { */
/* }; */

struct graph
{
  /* n soit le nombre de lignes */
  size_t n;
  /* m soit le nombre de colonnes */
  size_t m;
  /* m * n soit la taille de mat */
  size_t size;
  /* valeur infini pour les poids inf */
  int inf;
  /* malloc */
  void *mat;
  /* malloc */
  int *d;

  /* fonction cout */
  int (*cost)(int x, int y, struct graph *g);
  /* fonction de calcule des diagonlaes */
  int *(*diag)(int x, struct graph *g);
};

static inline int coord(int i, int j, size_t n)
{
  return i * n + j;
}

/* DEAD CODE */
struct graph *init_graph(size_t n, size_t m, int inf/* , enum g_type */);

void print_graph(struct graph g);

void print_array(int *t, size_t n);

void free_graph(struct graph *g);

#endif
