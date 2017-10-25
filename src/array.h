#ifndef ARRAY_H
# define ARRAY_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

struct array
{
  int *t;
  size_t cap;
  size_t size;
  int init_value;
};

struct array *init(size_t cap, int init_value);

struct array *add(int e, struct array *tab);

struct array *rm(int e, struct array *tab);

int exists(int e, struct array *tab);

void free_array(struct array *tab);

#endif
