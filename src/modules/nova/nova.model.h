#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <lib/index.h>


#define null NULL
#define annotation(...)

typedef struct let* let;

struct type {
  const char* name;
  void(*destructor)(let self);  
};
