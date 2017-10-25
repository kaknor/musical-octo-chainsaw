#include "stack.h"

void push(void *e, struct stack *s)
{
  if (s->size == s->cap)
    {
      s->s = realloc(s->s, s->cap * 2 * s->e_size);
      if (!s->s)
	    {
	      write(STDERR_FILENO, "s->s : fail to allocate in push\n", 28);
	      return;
	    }
      s->cap *= 2;
    }
  char *a = s->s;
  /* UNAUTHORIZED FUNCTION */
  memcpy(a + (s->size * s->e_size), e, s->e_size);
  s->size++;
}

void *pop(struct stack *s)
{
  if (!s->size)
    return NULL;
  char *a = s->s;
  void *res;
  if (!(res = malloc(s->e_size)))
    {
      write(STDERR_FILENO, "res : fail to allocate in pop\n", 28);
      return NULL;
    }
  /* UNAUTHORIZED FUNCTION */
  memcpy(res, a + (s->size - 1) * s->e_size, s->e_size);
  s->size--;
  return res;
}

struct stack *init_stack(size_t e_size, void (*e_free)(void *))
{
  struct stack *s = malloc(sizeof (struct stack));
  if (!s)
    {
      write(STDERR_FILENO, "s : fail to allocate in init_stac\n", 34);
      return NULL;
    }
  s->size = 0;
  s->cap = 8;
  s->e_size = e_size;
  s->s = malloc(e_size * s->cap);
  s->e_free = e_free;
  return s;
}

void free_stack(struct stack *s)
{
  if (s->e_free)
    for(size_t i = s->size; i > 0; i--)
      {
	char *c = s->s;
	s->e_free(c + i);
      }
  if (s)
    free(s);
}
