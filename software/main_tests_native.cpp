#include "synchronize.h"

#include <iostream>


extern "C" {
  int compare(uint32_t local, uint32_t distant);
}

void test_compare(int a, int b) {
  std::cout << a << " , " << b << " -> " << compare(a, b) << std::endl;
}

int main(int argc, char const *argv[]) {

  test_compare(0, 1);
  test_compare(1, 0);
  test_compare(0, 200);
  test_compare(100, 200);


  return 0;
}
