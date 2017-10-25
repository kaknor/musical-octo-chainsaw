#include "array.h"

struct array *init(size_t cap, int init_value)
{
  struct array *tab = malloc(sizeof (struct array));
  if (!tab)
    {
      write(STDERR_FILENO, "tab : allocation failed in init (array)\n", 40);
      return NULL;
    }
  tab->init_value = init_value;
  tab->cap = cap;
  tab->size = 0;
  tab->t = malloc(sizeof (int) * tab->cap);
  if (!tab->t)
    {
      write(STDERR_FILENO, "tab->t : allocation failed in init (array)\n", 43);
      return NULL;
    }
  for (size_t i = 0; i < tab->cap; i++)
    tab->t[i] = tab->init_value;
  return tab;
}

struct array *add(int e, struct array *tab)
{
  for (size_t i = 0; i < tab->cap; i++)
    {
      if (tab->t[i] == tab->init_value)
        {
          tab->t[i] = e;
	  tab->size++;
          break;
        }
    }
  return tab;
}

struct array *rm(int e, struct array *tab)
{
  for (size_t i = 0; i < tab->cap; i++)
    {
      if (tab->t[i] == e)
        {
          tab->t[i] = tab->init_value;
	  tab->size--;
          break;
        }
    }
  return tab;
}

int exists(int e, struct array *tab)
{
  for (size_t i = 0; i < tab->cap; i++)
    {
      if (tab->t[i] == e)
        return 1;
    }
  return 0;
}

int get_min(struct array *tab)
{
  int res = 0;
  for (size_t i = 0; i < tab->cap; i++)
    {
      if (tab->t[res] > tab->t[i])
        res = i;
    }
  return res;
}

void free_array(struct array *tab)
{
  if (tab->t)
    free(tab->t);
  if (tab)
    free(tab);
}
