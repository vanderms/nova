#pragma once
#include <modules/nova/nova.model.h>


struct nvnovaprimitivesi32 {
  let (*create)(int32_t value);
  int32_t (*get)(let self);
  void (*set)(let self, int32_t value);
};

extern const struct nvnovaprimitivesi32 nvnovaprimitivesi32_;
