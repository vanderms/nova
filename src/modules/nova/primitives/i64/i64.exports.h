#pragma once
#include <modules/nova/nova.model.h>


struct nvnovaprimitivesi64 {
  let (*create)(int64_t value);
  int64_t (*get)(let self);
  void (*set)(let self, int64_t value);
};

extern const struct nvnovaprimitivesi64 nvnovaprimitivesi64_;
