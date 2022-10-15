#include "i64.component.h"


static let nvconstructor(int64_t value){
  return nvnova_.build(create(value), &NVTYPE);
}

static void nvdestroy(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  destroy(self_);
}

static int64_t nvget(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  return get(self_);
}

static void nvset(let self, int64_t value){
  void* self_ = nvnova_.get(self, &NVTYPE);
  set(self_, value);
}

const struct nvnovaprimitivesi64 nvnovaprimitivesi64_ = {
  .create = nvconstructor,
  .get = nvget,
  .set = nvset,
};
