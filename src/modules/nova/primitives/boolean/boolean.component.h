#include "boolean.imports.h"
#include <stdlib.h>

annotation(import, modules.nova, nv)

annotation(type)
struct T {
  bool value;
};

annotation(constructor)
static T create(bool value){
  T self = nv.checkAllocation(malloc(sizeof(*self)));
  self->value = value;
  return self;
}

annotation(destructor)
static void destroy(T self){
  free(self);
}

annotation(method)
static bool get(T self){
  return self->value;
}

annotation(method)
static void set(T self, bool value){
  self->value = value;
}