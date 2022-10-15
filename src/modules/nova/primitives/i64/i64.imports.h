#pragma once
#include "i64.exports.h"
#include <modules/nova/nova.exports.h>

#define nv nvnova_
typedef struct T* T;

static T create(int64_t value);
static void destroy(T self);
static int64_t get(T self);
static void set(T self, int64_t value);
static void nvdestroy(let self);

static const struct type NVTYPE = {
  .hash = NV_LET_HASH,
  .name = "nova.primitives.i64",
  .destructor = nvdestroy
};
