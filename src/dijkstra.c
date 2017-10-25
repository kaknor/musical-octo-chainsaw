#include "dijkstra.h"

size_t choisirmin(struct array *M, int *ppd)
{
  size_t m = 0;
  for (size_t i = 0; i < M->cap; i++)
    {
      if (M->t[i] != -42)
        {
          if (M->t[m] == -42)
            m = i;
          if (ppd[i] == 1)
            {
              m = i;
              break;
            }
          if (ppd[m] > ppd[i])
            m = i;
        }
    }
  return m;
}

/* renvoi f pas du void  */
void dijkstra(int x_x, int x_y, struct graph *g, int *ppd, int *pred)
{
  struct array *M = init(g->size, -42);
  for (size_t i = 0; i < g->size; i++)
    {
      ppd[i] = g->cost(coord(x_x, x_y, g->m), i, g);
      pred[i] = coord(x_x, x_y, g->m);
      M = add(i, M);
    }
  M = rm(coord(x_x, x_y, g->m), M);
  while (M->size)
    {
      size_t m = choisirmin(M, ppd);
      if (M->t[m] == -42) /* cas d'arret, tous les sommets sont marques */
        return;
      M = rm(m, M);
      int *d = g->diag(m, g); /* malloc */
      for (size_t i = 0; i < 9; i++)
        {
          int y = d[i];
          if (y >= 0)
            {
              if (M->t[y] != -42)
                {
                  int v = ppd[m] + g->cost(m, y, g);
                  if (v < ppd[y])
                    {
                      ppd[y] = v;
                      pred[y] = m;
                    }
                }
            }
        }
      if (d)
        free(d);
    }
  free_array(M);
}

struct stack *get_path(int *pr, int x, int y, size_t e_size)
{
  struct stack *s = init_stack(e_size, NULL);
  int k = pr[y];
  while (k != x)
    {
      k = pr[y];
      push(&y, s);
      y = k;
    }
  push(&y, s);
  return s;
}

/* UNAUTHORIZED FUNCTION */
void print_path(int *pr, int x, int y)
{
  printf(" path : \n");
  int k = pr[y];
  while (k != x)
    {
      k = pr[y];
      printf("%d\n", y);
      y = k;
    }
  printf("%d\n", x);
}
