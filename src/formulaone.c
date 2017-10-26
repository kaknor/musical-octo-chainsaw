#include "control.h"

#define MAXSPEED 0.06
#define MAXSPEED2 0.015

#define INF 2000000

struct context =
  {
    struct stack *traj;
    struct graph *g;
    /* sommet courant */
    int curr;
    /* sommet a atteindre */
    int next;
    /* sommet de depart */
    int start;
    /* sommet final */
    int finish;
  };

struct context *g_context = NULL;


enum move update(struct car *car)
{
  if (!g_context)
    {
      /* pas sur si c'est height ou width */
      g_context->g = init_graph(c->map->width, c->map->height, INF);
      g_context->g->mat = car->map;
      int *pred = malloc(sizeof (int) * g_context->size);
      int *ppd = malloc(sizeof (int) * g_context->size);
      int s_x = map_get_start_x(car->map);
      int s_y = map_get_start_y(car->map);
      g_context->start = coord(s_x, s_y, );
      dijkstra(car->map->start.x, , g, ppd, pred);//TODO:ici tu passe les bon argument et tu stoke tes data dans *traj dans ta fonction directement
      g_context->traj = get_path(pr, g->start, g->finish, sizeof (int));
    }
  return choose_action(car);
}

//check si la car est sur le permier point de ta stack
int check_pos(struct car *car)
{
  car = car;
  //TODO si la car est sur le premier point de la stack alors le tej et mettre a jour la variable *traj
  //ne pas oublier du padding pour le check (on est pas forcement au centre de la case ex :
  //stack->next->x < car->pos->x + 0.78 || stack->next->x > car->pos->x + 0.78 //0.78 etant une valeur ayant fais ses preuves mais moins precise que la mienne je te laisserai la paufiner ;)
}

enum move choose_action(struct car *car)
{
  if (checkpos(&car->position, /*TODO le premier point de ta stack*/))
    //TODO pop un element de ta stack
  struct vector2 next;
  next.x = //TODO stack.top().x;
  next.y = //TODO stack.top().y;
  struct vector2 dir = getvect(car->position, next);
  if (colinear(car->direction, dir))//si on est dans la bonne direction
  {
    if (vitesse(car, MAXSPEED) || /*TODO taille de ta stack*/ == 1)
        return ACCELERATE;
    return DO_NOTHING;
  }
  else
  {
    if (vitesse(car, MAXSPEED2) || /*TODO taille de ta stack*/ == 1)
    {
      if (angleToInt(car->direction, dir) < 0)
        return  ACCELERATE_AND_TURN_LEFT;
      else
        return ACCELERATE_AND_TURN_RIGHT;
    }
    else
    {
      if (angleToInt(car->direction, dir) < 0)
        return TURN_LEFT;
      else
        return TURN_RIGHT;
    }
  }

}

//la direction de la f1 vers le next point
struct vector2 getvect(struct vector2 u, struct vector2 v)
{
  v.x -= u.x;
  v.y -= u.y;
  return v;
}


//********************VECTOR PART
float norme(struct vector2 u)
{
  return sqrt(u.x * u.x + u.y * u.y);
}
int colinear(struct vector2 u, struct vector2 v)
{
  return (norme(u) * norme(v) - produitvectoriel(u, v) < 0.02)? 1 : 0;
}

float produitvectoriel(struct vector2 u, struct vector2 v)
{
  return  u.y * v.y + u.x * v.x;
}
float angleToInt(struct vector2 u, struct vector2 v)
{
  float dot = produitvectoriel(u, v);
  float det = u.x * v.y - u.y * v.x;
  return atan2(det, dot); //TODO needs math.h
}

//distance euclidienne
float dist_eucl(struct vector2 u, struct vector2 v)
{
  return sqrt((u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y));
}

//********************UTILS PART
int vitesse(struct car *car, float vitessemax)
{
  return (car->speed.x > -vitessemax 
    && car->speed.y > -vitessemax
    && car->speed.x < vitessemax
    && car->speed.y < vitessemax);
}


//test si trois point sont allignés
int alligner(struct vector2 u, struct vector2 v, struct vector2 z)
{
    return (dist_eucl(u, v) + dist_eucl(v, z) >= dist_eucl(u, z) - 0.01)
    && (dist_eucl(u, v) + dist_eucl(v, z) <= dist_eucl(u, z) + 0.01);
}
