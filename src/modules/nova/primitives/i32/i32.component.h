#include "i32.imports.h"
annotation(import | modules.nova | nv)

annotation(type)
struct primitive {
  int32_t value;
};

annotation(constructor)
static primitive create(int32_t value){
  primitive self = nv.checkAllocation(malloc(sizeof(*self)));
  self->value = value;
  return self;
}

annotation(method)
static int32_t get(primitive self){
  return self->value;
}

annotation(method)
static void set(primitive self, int32_t value){
  self->value = value;
}