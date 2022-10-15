#include "app.imports.h"
#include <stdio.h>
annotation(import, modules.nova.primitives.i32, integer)
annotation(import, modules.nova, nv)
annotation(import, modules.nova.containers.array, array)

int main(void){
  
  let numbers = array.create(true);
  for(int i = 0; i < 100; i++){
    array.push(numbers, integer.create(i));
  }

  for(int i = 0; i < 100; i++){
    let number = array.get(numbers, i);
    printf("%d\n", integer.get(number));
  }

  nv.cleanup(&numbers);
  return 0;
}