#include <let/let.imports.h>
#include <let/let.model.h>


export static void* allocate(size_t size){
  void* memory = malloc(sizeof(size));
  if(memory == null){
    fprintf(stderr, "Fatal error. Failed to allocate memory.");
    exit(EXIT_FAILURE);    
  }
  return memory;
}


static inline void assertNonNull(let self){
  if(self == null){  
    fprintf(stderr, "Fatal error. Let module. Non null assertion.");
    exit(EXIT_FAILURE);    
  }
}


static inline void assertHash(let self){
  if(self->hash != HASH){
    fprintf(stderr, "Fatal error. Let module. Hash assertion.");
    exit(EXIT_FAILURE);
  }
}


void assertType(let self, Type* type){
  if(self->type != type){
    fprintf(stderr, "Fatal error. Let module. Type assertion.");
    exit(EXIT_FAILURE);
  }  
}


export static let build(void* value, Type* type){  
  struct let model = {
    .hash = HASH,
    .type = type,    
    .value = value
  };
  let self = memcpy(allocate(sizeof(struct let)), &model, sizeof(struct let));
  return self;
}


export static void delete(let self){
  if(self == null){
    return;
  }
  assertHash(self);
  self->type->destructor(self);
  self->hash = 0;
  free(self);
}


export static void* getp(let self, Type* type){
  assertNonNull(self);
  assertHash(self);
  assertType(self, type);
  return self->value.object;
} 
