#pragma once
#include "array.exports.h"
#include <modules/nova/nova.exports.h>

#define nv nvnova_
typedef struct Array* Array;

static Array create(bool collect);
static void destructor(Array self);
static uint32_t size(Array self);
static uint32_t capacity(Array self);
static let get(Array self, uint32_t index);
static void set(Array self, uint32_t index, let value);
static void push(Array self, let value);
static void pull(Array self, uint32_t index);
static uint32_t position(Array self, let value);
static void reserve(Array self, uint32_t capacity);
static void clean(Array self);
static void nvdestructor(let self);

static const struct type NVTYPE = {
  .hash = NV_LET_HASH,
  .name = "nova.containers.array",
  .destructor = nvdestructor
};
