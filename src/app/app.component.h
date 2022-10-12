#include "app.imports.h"
import(primitives.i32, integer)
import(primitives.i64, i64)
import(let, lt)


int main(void){
  let number = integer->create(10);
  printf("%d\n", integer->get(number));
  lt->cleanup(&number);  
  return 0;
}