#include "i32.component.h"


static let nvconstructor(int32_t value){
  return nvnova_.build(create(value), &NVTYPE);
}

static void nvdestroy(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  destroy(self_);
}

static int32_t nvget(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  return get(self_);
}

static void nvset(let self, int32_t value){
  void* self_ = nvnova_.get(self, &NVTYPE);
  set(self_, value);
}

const struct nvnovaprimitivesi32 nvnovaprimitivesi32_ = {
  .create = nvconstructor,
  .get = nvget,
  .set = nvset,
};
