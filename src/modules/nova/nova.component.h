#include "nova.private.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct let* let;

struct let {
  const struct type* type;
  void* value;
};


annotation(static)
static void* checkAllocation(void* memory){  
  if(memory == null){
    fprintf(stderr, "Fatal error in let module: failed to allocate memory.");
    exit(EXIT_FAILURE);    
  }  
  return memory;
}

annotation(static, hello, what)
static void println(const char* message){
  printf("%s\n", message);
}

annotation(static)
static void print(const char* message){
  printf("%s", message);
}

annotation(static)
static void assert(bool condition, const char* message){
  if(!condition){
    fprintf(stderr, "%s", message);
    exit(EXIT_FAILURE);
  }
}

static inline void assertNonNull(let self){
  if(self == null){  
    fprintf(stderr, "Fatal error in let module: non null assertion.");
    exit(EXIT_FAILURE);
  }
}

static inline void assertType(let self, const struct type* type){ 
  if(self->type != type){
    fprintf(stderr, "Fatal error in let module: type assertion.");
    exit(EXIT_FAILURE);
  }  
}

annotation(static)
static let build(void* value, const struct type* type){  
  struct let model = {    
    .type = type,    
    .value = value
  };
  void* memory = checkAllocation(malloc(sizeof model));
  let self = memcpy(memory, &model, sizeof model);
  return self;
}

annotation(static)
static void cleanup(let* ref){
  if(ref == null || *ref == null){
    return;
  }

  let self = *ref;  
  if(self->type->hash != NV_LET_HASH){
    fprintf(stderr, "Fatal error in let.cleanup method: incorrect hash value.");
    exit(EXIT_FAILURE);    
  }

  if(self->type->destructor == null){
    free(self->value);
  }
  else { 
    self->type->destructor(self);   
  }

  self->type = null;
  free(self);
  ref = null;
}

annotation(static)
static void* get(let self, const struct type* type){
  assertNonNull(self); 
  assertType(self, type);
  return self->value;  
}


annotation(static)
static const struct type* type(let self){
  assertNonNull(self);  
  return self->type;
}

annotation(static)
static bool is(let self, const struct type* type){
  assertNonNull(self); 
  return self->type == type;
}
