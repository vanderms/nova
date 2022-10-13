#include "f64.imports.h"
import(let, lt);


struct f64 {
  double value;
};

typedef struct f64* f64;

static struct type TYPE = {
  .name = "f64",
  .compare = compare,
  .destructor = destructor,
};

export static let create(double value){
  f64 self = lt->allocate(sizeof(*self));
  self->value = value;
  return lt->build(self, &TYPE);
}

static void destructor (let self){
  f64 this = lt->get(self, &TYPE);
  free(this);
}

export static double get(let self){
  f64 this = lt->get(self, &TYPE);
  return this->value;
}

export static void set(let self, double value){
  f64 this = lt->get(self, &TYPE);
  this->value = value;
}

static int32_t compare(let self, let other){
  f64 s = lt->get(self, &TYPE);
  f64 o = lt->get(other, &TYPE);
  if(s->value > o->value){
    return 1;
  }
  if(o->value > s->value){
    return -1;
  }
  return 0;
}
