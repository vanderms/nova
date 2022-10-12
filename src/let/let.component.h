#include <let/let.imports.h>
#include <let/let.model.h>


/*Memory allocation*/
export static void* allocate(size_t size){
  void* memory = malloc(sizeof(size));
  if(memory == null){
    fprintf(stderr, "Fatal error in let module: failed to allocate memory.");
    exit(EXIT_FAILURE);    
  }  
  return memory;
}

/*Assertions*/
static inline void assertNonNull(let self){
  if(self == null){  
    fprintf(stderr, "Fatal error in let module: non null assertion.");
    exit(EXIT_FAILURE);    
  }
}


static void assertType(let self, const struct type* type){
  if(self->type != type){
    fprintf(stderr, "Fatal error in let module: struct type assertion.");
    exit(EXIT_FAILURE);
  }  
}


/*Main methods*/
export static let build(void* value, const struct type* type){  
  struct let model = {    
    .type = type,    
    .value = value
  };
  let self = memcpy(allocate(sizeof(struct let)), &model, sizeof(struct let));
  return self;
}


export static void cleanup(let* ref){
  if(ref == null || *ref == null){
    return;
  } 
  let self = *ref;
  
  if(self->type->destructor){
    self->type->destructor(self);
  }  
  self->type = null;
  free(self);
  ref = null;
}


export static void* get(let self, const struct type* type){
  assertNonNull(self); 
  assertType(self, type);
  return self->value;
} 


export static const struct type* getType(let self){
  assertNonNull(self);  
  return self->type;
}

export static bool is(let self, const struct type* type){
  assertNonNull(self); 
  return self->type == type;
}
