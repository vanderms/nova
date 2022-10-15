#pragma once
#include <modules/nova/nova.model.h>


struct nvnovacontainersarray {
  let (*create)(bool collect);
  uint32_t (*size)(let self);
  uint32_t (*capacity)(let self);
  let (*get)(let self, uint32_t index);
  void (*set)(let self, uint32_t index, let value);
  void (*push)(let self, let value);
  void (*pull)(let self, uint32_t index);
  uint32_t (*position)(let self, let value);
  void (*reserve)(let self, uint32_t capacity);
  void (*clean)(let self);
};

extern const struct nvnovacontainersarray nvnovacontainersarray_;
