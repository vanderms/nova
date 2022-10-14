#include "nova.component.h"


const struct nvnova nvnova_ = {
  .checkAllocation = checkAllocation,
  .build = build,
  .cleanup = cleanup,
  .get = get,
  .type = type,
  .is = is,
};
