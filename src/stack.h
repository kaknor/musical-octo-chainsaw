#ifndef STACK_H
# define STACK_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

struct stack
{
  size_t size;
  size_t cap;
  size_t e_size;
  void *s;

  void (*e_free)(void *);
};

/* UNAUTHORIZED FUNCTION */
void *pop(struct stack *s);

/* UNAUTHORIZED FUNCTION */
void push(void *e, struct stack *s);

struct stack *init_stack(size_t e_size, void (*free_stack)(void *));

void free_stack(struct stack *s);
#endif
