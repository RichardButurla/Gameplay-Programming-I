#include <iostream>
#include <./include/calculator.h>

int main() {
  // The following will generate a warning message 
  // Comment out one of the next to explore what happens 
  int a;
  a = 10;
  std::cout << a << std::endl;

  std::cout << "Hey Phill";

  int b = 5;
  std::cout << "Multiple of " << a << " and " << b << " is: " << multiply(a, b);
  
  return(0);

  // In VSC debugging beyond this point will result in the following error message
  // Unable to open 'libc-start.c': Unable to read file '/build/glibc-eX1tMB/glibc-2.31/csu/libc-start.c' 
  // (Error: Unable to resolve non-existing file '/build/glibc-eX1tMB/glibc-2.31/csu/libc-start.c').
  // Press F5 when you are finished stepping through code. This will avoid the VSC popup
}