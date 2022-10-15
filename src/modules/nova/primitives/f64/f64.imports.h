#pragma once
#include "f64.exports.h"
#include <modules/nova/nova.exports.h>

#define nv nvnova_
typedef struct T* T;

static T create(double value);
static void destroy(T self);
static double get(T self);
static void set(T self, double value);
static void nvdestroy(let self);

static const struct type NVTYPE = {
  .hash = NV_LET_HASH,
  .name = "nova.primitives.f64",
  .destructor = nvdestroy
};
