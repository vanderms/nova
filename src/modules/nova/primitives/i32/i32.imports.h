#pragma once
#include "i32.exports.h"
#include <modules/nova/nova.exports.h>

#define nv nvnova_
typedef struct T* T;

static T create(int32_t value);
static void destroy(T self);
static int32_t get(T self);
static void set(T self, int32_t value);
static void nvdestroy(let self);

static const struct type NVTYPE = {
  .hash = NV_LET_HASH,
  .name = "nova.primitives.i32",
  .destructor = nvdestroy
};
