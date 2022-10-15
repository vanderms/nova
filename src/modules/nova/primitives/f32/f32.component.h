#include "f32.imports.h"
#include <stdlib.h>
annotation(import, modules.nova, nv)


annotation(type)
struct T {
  float value;
};

annotation(constructor)
static T create(float value){
  T self = nv.checkAllocation(malloc(sizeof(*self)));
  self->value = value;
  return self;
}

annotation(destructor)
static void destroy(T self){
  free(self);
}

annotation(method)
static float get(T self){
  return self->value;
}

annotation(method)
static void set(T self, float value){
  self->value = value;
}