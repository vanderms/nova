#include "f32.component.h"


static let nvconstructor(float value){
  return nvnova_.build(create(value), &NVTYPE);
}

static void nvdestroy(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  destroy(self_);
}

static float nvget(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  return get(self_);
}

static void nvset(let self, float value){
  void* self_ = nvnova_.get(self, &NVTYPE);
  set(self_, value);
}

const struct nvnovaprimitivesf32 nvnovaprimitivesf32_ = {
  .create = nvconstructor,
  .get = nvget,
  .set = nvset,
};
