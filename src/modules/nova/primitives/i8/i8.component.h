#include "i8.imports.h"
#include <stdlib.h>
annotation(import, modules.nova, nv)

annotation(type)
struct T {
  char value;
};

annotation(constructor)
static T create(char value){
  T self = nv.checkAllocation(malloc(sizeof(*self)));
  self->value = value;
  return self;
}

annotation(destructor)
static void destroy(T self){
  free(self);
}

annotation(method)
static char get(T self){
  return self->value;
}

annotation(method)
static void set(T self, char value){
  self->value = value;
}