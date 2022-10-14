#include "app.imports.h"
annotation(import, modules.nova.primitives.i32, i32)
annotation(import, modules.nova, nv)

int main(void){
  
  let number = i32.create(10);
  i32.set(number, 12);
  printf("%d\n", i32.get(number));  
  nv.cleanup(&number);

  return 0;
}