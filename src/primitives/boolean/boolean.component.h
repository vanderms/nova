#include "boolean.imports.h"
import(let, lt);


struct boolean {
  bool value;
};

typedef struct boolean* boolean;

static struct type TYPE = {
  .name = "primitives.boolean",
  .compare = compare,
  .destructor = destructor,
};

export static let create(bool value){
  boolean self = lt->allocate(sizeof(*self));
  self->value = value;
  return lt->build(self, &TYPE);
}

static void destructor (let self){
  boolean this = lt->get(self, &TYPE);
  free(this);
}

export static bool get(let self){
  boolean this = lt->get(self, &TYPE);
  return this->value;
}

export static void set(let self, bool value){
  boolean this = lt->get(self, &TYPE);
  this->value = value;
}

static int32_t compare(let self, let other){
  boolean s = lt->get(self, &TYPE);
  boolean o = lt->get(other, &TYPE);
  if(s->value > o->value){
    return 1;
  }
  if(o->value > s->value){
    return -1;
  }
  return 0;
}
