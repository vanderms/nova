#include <let/let.imports.h>

union value {
  void* object;
  char* string;
  int32_t i32; 
  uint32_t u32;
  int64_t i64;
  uint64_t u64;
  float float32;
  double float64;
  bool boolean;
  char character;
};

struct let {
  int32_t hash;  
  struct type* const type;
  union value value;
};

static const int32_t HASH = 1238893793;