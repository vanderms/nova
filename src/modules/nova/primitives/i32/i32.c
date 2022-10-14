#include "i32.component.h"


static let nvconstructor(int32_t value){
  return nvnova_.build(create(value), &NVTYPE);
}

const struct nvnovaprimitivesi32 nvnovaprimitivesi32_ = {
  .create = nvconstructor,
};
