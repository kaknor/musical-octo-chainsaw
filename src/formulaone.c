#include "control.h"

#include "graphs.h"
#include "floyd.h"
#include "dijkstra.h"
#include "stack.h"

#define INF 2000000

static inline int cmp(float a, float b, float p)
{
  return (a <= b + p && a >= b - p);
}

static inline int cmp_lrg(float a, float b, float p)
{
  return (a < b + p && a > b - p);
}

enum move update(struct car *car)
{
  /* x est egale a j */
  float x = map_get_start_x(car->map);
  /* y est egale a i */
  float y = map_get_start_y(car->map);

  struct graph *g = init_graph(car->map->height, car->map->width, INF);
  if (g->mat)
    free(g->mat);
  g->mat = car->map;
  
  int *ppd = malloc(sizeof (int) * g->size);
  int *pred = malloc(sizeof (int) * g->size);

  dijkstra(y, x, g, ppd, pred);

  struct stack *s = get_path(pred, coord(y, x, g->m), coord(14, 52, g->m), sizeof (int));
  for (size_t i = s->size; i > 0; i--)
    {
      int *a = pop(s);
      /* UNAUTHORIZED FUNCTION */
      /* printf("%d\n", *a); */
      free(a);
    }
  free_stack(s);
  if (ppd)
    free(ppd);
  if (pred)
    free(pred);
  if (g->d)
    free(g->d);
  if (g)
    free(g);

  /* UNAUTHORIZED FUNCTION */
  printf("%f \n %f", car->direction_angle, M_PI / 2);

  if (cmp(car->direction_angle, M_PI / 2, 0))
    return TURN_LEFT;
  else
    return DO_NOTHING;
}
