#include <stdio.h>
 
void foo(int N) {
 printf("foo: %d in C++\n",N);
 N/=2;
 if(N >1 )
  foo(N);
}
 
int main() {
 
 foo(4);
 
 return 0;
}
