#include "nova.component.h"


const struct nvnova nvnova_ = {
  .checkAllocation = checkAllocation,
  .println = println,
  .print = print,
  .assert = assert,
  .build = build,
  .cleanup = cleanup,
  .get = get,
  .type = type,
  .is = is,
};
