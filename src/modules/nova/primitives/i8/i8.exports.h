#pragma once
#include <modules/nova/nova.model.h>


struct nvnovaprimitivesi8 {
  let (*create)(char value);
  char (*get)(let self);
  void (*set)(let self, char value);
};

extern const struct nvnovaprimitivesi8 nvnovaprimitivesi8_;
