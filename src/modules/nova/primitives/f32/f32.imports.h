#pragma once
#include "f32.exports.h"
#include <modules/nova/nova.exports.h>

#define nv nvnova_
typedef struct T* T;

static T create(float value);
static void destroy(T self);
static float get(T self);
static void set(T self, float value);
static void nvdestroy(let self);

static const struct type NVTYPE = {
  .hash = NV_LET_HASH,
  .name = "nova.primitives.f32",
  .destructor = nvdestroy
};
