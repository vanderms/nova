#include "i32.imports.h"
#include <stdlib.h>
annotation(import, modules.nova, nv)

annotation(type)
struct T {
  int32_t value;
};

annotation(constructor)
static T create(int32_t value){
  T self = nv.checkAllocation(malloc(sizeof(*self)));
  self->value = value;
  return self;
}

annotation(destructor)
static void destroy(T self){
  free(self);
}

annotation(method)
static int32_t get(T self){
  return self->value;
}

annotation(method)
static void set(T self, int32_t value){
  self->value = value;
}