#pragma once
#include "nova.exports.h"


static void* checkAllocation(void* memory);
static inline void assertNonNull(let self);
static inline void assertType(let self, const struct type* type);
static let build(void* value, const struct type* type);
static void cleanup(let* ref);
static void* get(let self, const struct type* type);
static const struct type* type(let self);
static bool is(let self, const struct type* type);
