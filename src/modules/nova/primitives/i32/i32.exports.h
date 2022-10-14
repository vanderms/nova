#pragma once
#include <modules/nova/nova.model.h>


struct nvnovaprimitivesi32 {
  let (*create)(int32_t value);
};

extern const struct nvnovaprimitivesi32 nvnovaprimitivesi32_;
