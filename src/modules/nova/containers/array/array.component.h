#include "array.imports.h"
#include <stdlib.h>
annotation(import, modules.nova, nv)

static const char* OUT_OF_BOUNDS_ERROR = "Runtime error. In modules.containers.array. Index out of bounds";
static const char* NULL_VALUE_ERROR = "Runtime error. In modules.containers.array. Value cannot be null";


annotation(type)
struct Array {	
    let* entries;    
    uint32_t size;
    uint32_t capacity;
    bool collect;
};


annotation(constructor)
static Array create(bool collect){
	Array self = nv.checkAllocation(malloc(sizeof(*self)));    
  self->entries = nv.checkAllocation(malloc(sizeof(*self->entries) * 8));    
  self->capacity = 8;
  self->size = 0;
  self->collect = collect;
  return self;
}


annotation(destructor)
static void destructor(Array self) {  
  if (self->collect) {
    for (uint32_t i = 0; i < self->size; i++) {
      nv.cleanup(&self->entries[i]);
    }
  }    
  free(self->entries);        
  free(self);
}


annotation(method)
static uint32_t size(Array self){    
	return self->size;
}


annotation(method)
static uint32_t capacity(Array self){    
	return self->capacity;
}


annotation(method)
static let get(Array self, uint32_t index) {
  nv.assert(index < self->size, OUT_OF_BOUNDS_ERROR);
  return self->entries[index];
}


annotation(method)
static void set(Array self, uint32_t index, let value) {
    nv.assert(value != null, NULL_VALUE_ERROR);
    nv.assert(index < self->size, OUT_OF_BOUNDS_ERROR);
    if (self->collect) {
        nv.cleanup(&self->entries[index]);
    }    
    self->entries[index] = value;
}


annotation(method)
static void push(Array self, let value){   
  self->size++; 
  if (self->size >= self->capacity) {
    reserve(self, 2 * self->capacity);
  }
  self->entries[self->size - 1] = value;
}


annotation(method)
static void pull(Array self, uint32_t index) {
    nv.assert(index < self->size, OUT_OF_BOUNDS_ERROR);   
    if (self->collect) {
        nv.cleanup(&self->entries[index]);
    }
    for (uint32_t i = index; i < self->size - 1; i++) {
        self->entries[i] = self->entries[i + 1];
    }
    self->size--;
}

annotation(method)
static uint32_t position(Array self, let value) {    
  uint32_t index = self->size;
  for (uint32_t i = 0; i < self->size; i++) {
    if (value == get(self, i)) {
      index = i;
      break;
    }
  }
  return index;
}


annotation(method)
static void reserve(Array self, uint32_t capacity) {
  if (self->capacity >= capacity){
    return;
  } 
  self->entries = nv.checkAllocation(realloc(self->entries, sizeof(*self->entries) * capacity));
  self->capacity = capacity;
}

annotation(method)
static void clean(Array self) {  
  if(self->size > 0 || self->capacity > 8){
    if (self->collect) {
      for (uint32_t i = 0; i < self->size; i++) {
        nv.cleanup(&self->entries[i]);
      }
    }
    free(self->entries);
    self->entries = nv.checkAllocation(malloc(sizeof(*self->entries) * 8));
    self->capacity = 8;
    self->size = 0;
  }
}

