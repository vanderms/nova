#pragma once
#include <modules/nova/nova.model.h>


struct nvnovaprimitivesf32 {
  let (*create)(float value);
  float (*get)(let self);
  void (*set)(let self, float value);
};

extern const struct nvnovaprimitivesf32 nvnovaprimitivesf32_;
