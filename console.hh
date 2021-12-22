#pragma once

#include "string.hh"
#include "sysdef.hh"
#include "vga.hh"

#define TEXT_MODE_WIDTH 80
#define TEXT_MODE_HEIGHT 25

namespace base {

struct cursor_t {
  size_t row, column;

  cursor_t() : row(), column() {}

  size_t index() { return row * TEXT_MODE_WIDTH + column; }

  void set_pos(size_t row, size_t column) {
    this->row = row;
    this->column = column;
  }
};

struct console {
  cursor_t cursor;
  uint8_t color;
  uint16_t *buffer;

  console(vga::color fg = vga::WHITE, vga::color bg = vga::BLUE)
      : cursor(), color(vga::entry_color(fg, bg)), buffer((uint16_t *)0xb8000) {
    fill(' ');
  }

  size_t pos(size_t row, size_t column) {
    return row * TEXT_MODE_WIDTH + column;
  }

  void set_pos(size_t row, size_t column) { cursor.set_pos(row, column); }

  void fill(uint8_t c) {
    for (size_t __row{}; __row < TEXT_MODE_HEIGHT; ++__row)
      for (size_t __col{}; __col < TEXT_MODE_WIDTH; ++__col)
        buffer[pos(__row, __col)] = vga::entry(c, color);
  }

  void set_color(uint8_t color) { this->color = color; }

  void put_entry_at(char c, uint8_t color, cursor_t cur) {
    buffer[cur.index()] = vga::entry(c, color);
  }

  void putc(char c) {
    put_entry_at(c, color, cursor);
    if (++cursor.column == TEXT_MODE_WIDTH) {
      cursor.column = 0;
      if (++cursor.row == TEXT_MODE_HEIGHT)
        cursor.row = 0;
    }
  }

  void puts(const char *str) {
    auto size = strlen(str);
    for (size_t i{}; i < size; ++i)
      putc(str[i]);
  }
};

} // namespace base
