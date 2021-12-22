#include "console.hh"

extern "C" int kernel_main(int, char **) {
  base::console console;

  console.puts("Hello, Kernel!!");
  console.putc('~');
  console.set_pos(20, 40);
  console.puts("Hello, Kernel!!");
  console.set_pos(10, 20);
  console.putc('~');

  return 0;
}
