#include "f64.component.h"


static let nvconstructor(double value){
  return nvnova_.build(create(value), &NVTYPE);
}

static void nvdestroy(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  destroy(self_);
}

static double nvget(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  return get(self_);
}

static void nvset(let self, double value){
  void* self_ = nvnova_.get(self, &NVTYPE);
  set(self_, value);
}

const struct nvnovaprimitivesf64 nvnovaprimitivesf64_ = {
  .create = nvconstructor,
  .get = nvget,
  .set = nvset,
};
