#include "graphs.h"

int *init_diag(size_t m)
{
  int *diag = malloc(sizeof (int) * 9);
  if (!diag)
    {
      write(STDERR_FILENO, "diag : allocation failed in init_diag\n", 33);
      return diag;
    }
  int d[9] =
    {
      // upper left
      -m - 1,
      // up
      -m,
      // upper right
      -m + 1,
      // left
      -1,
      // self
      0,
      // right
      1,
      // lower left
      m - 1,
      // low
      m,
      // lower right
      m + 1
    };
  for (size_t i = 0; i < 9; i++)
    diag[i] = d[i];
  return diag;
}

int *diag(int x, struct graph *g)
{
  int m = g->m;
  int *d = malloc(sizeof (int) * 9);
  if (!d)
    {
      write(STDERR_FILENO, "d : allocation failed in diag\n", 33);
      return d;
    }
  for (size_t i = 0; i < 9; i++)
    d[i] = -1;
  for (size_t i = 0; i < 9; i++)
    {
      int res = x + g->d[i];
      int g_size = g->size;
      if (res >= 0 && res < g_size)
        {
          if (i == 0 || i == 1 || i == 2)
            if (res >= m * (x / m - 1) && res <= m * (x / m - 1) + m - 1)
              d[i] = res;
          if (i == 3 || i == 4 || i == 5)
            if (res >= m * (x / m) && res <= m * (x / m) + m - 1)
              d[i] = res;
          if (i == 6 || i == 7 || i == 8)
            if (res >= m * (x / m + 1) && res <= m * (x / m + 1) + m - 1)
              d[i] = res;
        }
    }
  return d;
}

int cost(int x, int y, struct graph *g)
{
  if (x == y)
    return 0;
  /* g->diag changer par map_get_floor */
  int *d = g->diag(x, g)
  int *g_mat = g->mat;
  for (size_t i = 0; i < 9; i++)
    {
      if (d[i] == y)
        {
          free(d);
          return g_mat[y];
        }
    }
  free(d);
  /* INF */
  return g->inf;
}

/* TODO : faire un fichier a part avec get_i dedans */
static inline size_t get_i(size_t x, struct graph *g)
{
  return (x - (x % g->m)) / g->m;
}

/* TODO : faire un fichier a part avec get_j dedans */
static inline size_t get_j(size_t x, size_t i, struct graph *g)
{
  return x - i * g->m;
}

/* TODO : rm cette fonction (fonction de test) */
static inline enum floortype test_map_get_floor(struct graph *g, int i, int j)
{
  char *map = g->mat;
  size_t m = g->m;
  return (map[coord(i, j, m)] == 'r') * ROAD
    + (map[coord(i, j, m)] == 'g') * GRASS
    + (map[coord(i, j, m)] == 'b') * BLOCK
    + (map[coord(i, j, m)] == 'f') * FINISH;
}

/* TODO : laisse le call a map_get_floor une fois le test fini */
/* TODO : faire un fichier a part avec edge_cost dedans */
/* DEAD CODE */
int edge_cost(int x, struct graph *g)
{
  size_t i = get_i(x, g);
  size_t j = get_j(x, i, g);
  enum floortype t = map_get_floor(g->mat, i, j);
  /* enum floortype t = test_map_get_floor(g, i, j); */
  return (t == ROAD) * 1
    + (t == GRASS) * 2
    + (t == BLOCK) * g->inf
    + (t == FINISH) * 3;
}

/* TODO : faire un fichier cost.[hc] avec les fonctions de couts dedans */
int cost_char(int x, int y, struct graph *g)
{
  if (x == y)
    return 0;
  int *d = g->diag(x, g);
  for (size_t i = 0; i < 9; i++)
    {
      if (d[i] == y)
        {
          free(d);
          return edge_cost(y, g);
        }
    }
  free(d);
  /* INF */
  return g->inf;
}

/* DEAD CODE */
struct graph *init_graph(size_t n, size_t m, int inf/* , size_t g_type */)
{
  /* UNAUTHORIZED FUNCTION  CALLOC */
  struct graph *g = calloc(n * m, sizeof (struct graph));
  if (!g)
    {
      write(STDERR_FILENO, "g : allocation failed in init_graph\n", 33);
      return g;
    }
  g->inf = inf;
  g->n = n;
  g->m = m;
  g->size = m * n;
  g->d = init_diag(g->m);
  g->diag = diag;
  /* fonction de cout */
  g->cost = cost_char;
  return g;
}

/* TODO : a remplacer par des fonctions map */
/* TODO : rm printf */
/* UNAUTHORIZED FUNCTION : printf */
void print_graph(struct graph g)
{
  size_t c = 0;
  /* la ou la genericte prends place */
  int *g_mat = g.mat;
  for (size_t i = 0; i < g.size; i++)
    {
      if (c > g.m - 1)
        {
          printf("\n");
          c = 0;
        }
      printf("%d ", g_mat[i]);
      c++;
    }
}
/* TODO : rm */
/* UNAUTHORIZED FUNCTION : printf */
void print_array(int *t, size_t n)
{
  for (size_t i = 0; i < n; i++)
    {
      for (size_t j = 0; j < n; j++)
        printf("%d ", t[coord(i, j, n)]);
      printf("\n");
    }
  printf("\n");
}

void free_graph(struct graph *g)
{
  if (g->mat)
    free(g->mat);
  if (g->d)
    free(g->d);
  if (g)
    free(g);
}
