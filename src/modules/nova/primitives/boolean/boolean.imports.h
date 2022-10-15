#pragma once
#include "boolean.exports.h"
#include <modules/nova/nova.exports.h>

#define nv nvnova_
typedef struct T* T;

static T create(bool value);
static void destroy(T self);
static bool get(T self);
static void set(T self, bool value);
static void nvdestroy(let self);

static const struct type NVTYPE = {
  .hash = NV_LET_HASH,
  .name = "nova.primitives.boolean",
  .destructor = nvdestroy
};
