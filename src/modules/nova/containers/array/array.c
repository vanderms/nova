#include "array.component.h"


static let nvconstructor(bool collect){
  return nvnova_.build(create(collect), &NVTYPE);
}

static void nvdestructor(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  destructor(self_);
}

static uint32_t nvsize(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  return size(self_);
}

static uint32_t nvcapacity(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  return capacity(self_);
}

static let nvget(let self, uint32_t index){
  void* self_ = nvnova_.get(self, &NVTYPE);
  return get(self_, index);
}

static void nvset(let self, uint32_t index, let value){
  void* self_ = nvnova_.get(self, &NVTYPE);
  set(self_, index,value);
}

static void nvpush(let self, let value){
  void* self_ = nvnova_.get(self, &NVTYPE);
  push(self_, value);
}

static void nvpull(let self, uint32_t index){
  void* self_ = nvnova_.get(self, &NVTYPE);
  pull(self_, index);
}

static uint32_t nvposition(let self, let value){
  void* self_ = nvnova_.get(self, &NVTYPE);
  return position(self_, value);
}

static void nvreserve(let self, uint32_t capacity){
  void* self_ = nvnova_.get(self, &NVTYPE);
  reserve(self_, capacity);
}

static void nvclean(let self){
  void* self_ = nvnova_.get(self, &NVTYPE);
  clean(self_);
}

const struct nvnovacontainersarray nvnovacontainersarray_ = {
  .create = nvconstructor,
  .size = nvsize,
  .capacity = nvcapacity,
  .get = nvget,
  .set = nvset,
  .push = nvpush,
  .pull = nvpull,
  .position = nvposition,
  .reserve = nvreserve,
  .clean = nvclean,
};
