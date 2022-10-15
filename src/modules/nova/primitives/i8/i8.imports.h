#pragma once
#include "i8.exports.h"
#include <modules/nova/nova.exports.h>

#define nv nvnova_
typedef struct T* T;

static T create(char value);
static void destroy(T self);
static char get(T self);
static void set(T self, char value);
static void nvdestroy(let self);

static const struct type NVTYPE = {
  .hash = NV_LET_HASH,
  .name = "nova.primitives.i8",
  .destructor = nvdestroy
};
