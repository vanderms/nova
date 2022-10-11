#pragma once
#include "let.exports.h"


static void* allocate(size_t size);
static inline void assertNonNull(let self);
static inline void assertHash(let self);
static let build(void* value, Type* type);
static void delete(let self);
static void* getp(let self, Type* type);
