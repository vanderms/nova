#include "i32.imports.h"
import(let, lt);


struct i32 {
  int32_t value;
};

typedef struct i32* i32;

struct type TYPE = {
  .name = "i32",
  .compare = compare,
  .destructor = destructor,
};

export static let create(int32_t value){
  i32 self = lt->allocate(sizeof(*self));
  self->value = value;
  return lt->build(self, &TYPE);
}

static void destructor (let self){
  i32 this = lt->get(self, &TYPE);
  free(this);
}

export static int32_t get(let self){
  i32 this = lt->get(self, &TYPE);
  return this->value;
}

export static void set(let self, int32_t value){
  i32 this = lt->get(self, &TYPE);
  this->value = value;
}

static int32_t compare(let self, let other){
  i32 s = lt->get(self, &TYPE);
  i32 o = lt->get(other, &TYPE);
  if(s->value > o->value){
    return 1;
  }
  if(o->value > s->value){
    return -1;
  }
  return 0;
}