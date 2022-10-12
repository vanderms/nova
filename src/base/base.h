#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <lib/index.h>

#define export
#define import(module, as)

#define null NULL

typedef struct let* let;

struct type {
  void(*destructor)(let self); 
  int32_t (*compare)(let self, let other);
  const char* name;
};