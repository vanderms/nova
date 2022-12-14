#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <lib/index.h>

#define null NULL
#define annotation(...)

typedef struct let* let;

struct type {
  uint32_t hash;
  const char* name;
  void(*destructor)(let self);  
};

static const uint32_t NV_LET_HASH = 0x4ad7f3b;