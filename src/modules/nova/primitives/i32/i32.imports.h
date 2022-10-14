#pragma once
#include "i32.exports.h"
#include <modules/nova/nova.exports.h>

#define nv nvnova_
typedef struct primitive* primitive;

static primitive create(int32_t value);
static int32_t get(primitive self);
static void set(primitive self, int32_t value);

static const struct type NVTYPE = {
  .hash = NV_LET_HASH,
  .name = "nova.primitives.i32",
  .destructor = null
};
