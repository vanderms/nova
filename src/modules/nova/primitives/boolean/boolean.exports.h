#pragma once
#include <modules/nova/nova.model.h>


struct nvnovaprimitivesboolean {
  let (*create)(bool value);
  bool (*get)(let self);
  void (*set)(let self, bool value);
};

extern const struct nvnovaprimitivesboolean nvnovaprimitivesboolean_;
