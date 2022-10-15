#include "boolean.component.h"


static let nvconstructor(bool value){
  return nvnova_.build(create(value), &NVTYPE);
}

static void nvdestroy(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  destroy(self_);
}

static bool nvget(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  return get(self_);
}

static void nvset(let self, bool value){
  void* self_ = nvnova_.get(self, &NVTYPE);
  set(self_, value);
}

const struct nvnovaprimitivesboolean nvnovaprimitivesboolean_ = {
  .create = nvconstructor,
  .get = nvget,
  .set = nvset,
};
