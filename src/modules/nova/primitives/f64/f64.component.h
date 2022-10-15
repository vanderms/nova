#include "f64.imports.h"
#include <stdlib.h>
annotation(import, modules.nova, nv)

annotation(type)
struct T {
  double value;
};

annotation(constructor)
static T create(double value){
  T self = nv.checkAllocation(malloc(sizeof(*self)));
  self->value = value;
  return self;
}

annotation(destructor)
static void destroy(T self){
  free(self);
}

annotation(method)
static double get(T self){
  return self->value;
}

annotation(method)
static void set(T self, double value){
  self->value = value;
}