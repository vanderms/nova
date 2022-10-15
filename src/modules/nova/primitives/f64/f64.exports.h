#pragma once
#include <modules/nova/nova.model.h>


struct nvnovaprimitivesf64 {
  let (*create)(double value);
  double (*get)(let self);
  void (*set)(let self, double value);
};

extern const struct nvnovaprimitivesf64 nvnovaprimitivesf64_;
