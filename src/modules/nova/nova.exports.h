#pragma once
#include <modules/nova/nova.model.h>


struct nvnova {
  void* (*checkAllocation)(void* memory);
  void (*println)(const char* message);
  void (*print)(const char* message);
  void (*assert)(bool condition, const char* message);
  let (*build)(void* value, const struct type* type);
  void (*cleanup)(let* ref);
  void* (*get)(let self, const struct type* type);
  const struct type* (*type)(let self);
  bool (*is)(let self, const struct type* type);
};

extern const struct nvnova nvnova_;
