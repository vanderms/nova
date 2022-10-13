#include "i64.imports.h"
import(let, lt);


struct i64 {
  int64_t value;
};

typedef struct i64* i64;

static struct type TYPE = {
  .name = "i64",
  .compare = compare,
  .destructor = destructor,
};

export static let create(int64_t value){
  i64 self = lt->allocate(sizeof(*self));
  self->value = value;
  return lt->build(self, &TYPE);
}

static void destructor (let self){
  i64 this = lt->get(self, &TYPE);
  free(this);
}

export static int64_t get(let self){
  i64 this = lt->get(self, &TYPE);
  return this->value;
}

export static void set(let self, int64_t value){
  i64 this = lt->get(self, &TYPE);
  this->value = value;
}

static int32_t compare(let self, let other){
  i64 s = lt->get(self, &TYPE);
  i64 o = lt->get(other, &TYPE);
  if(s->value > o->value){
    return 1;
  }
  if(o->value > s->value){
    return -1;
  }
  return 0;
}
