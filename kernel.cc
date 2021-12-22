#include "console.hh"

extern "C" int kernel_main(int, char **) {
  base::console console;

  for (;;) {
    console.puts("Hello, Kernel!!");
  }

  return 0;
}
