#include "i8.component.h"


static let nvconstructor(char value){
  return nvnova_.build(create(value), &NVTYPE);
}

static void nvdestroy(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  destroy(self_);
}

static char nvget(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  return get(self_);
}

static void nvset(let self, char value){
  void* self_ = nvnova_.get(self, &NVTYPE);
  set(self_, value);
}

const struct nvnovaprimitivesi8 nvnovaprimitivesi8_ = {
  .create = nvconstructor,
  .get = nvget,
  .set = nvset,
};