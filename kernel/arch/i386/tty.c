#include "vga.h"
#include <kernel/tty.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define VGA_DEFAULT_COLOR vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK)

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t *const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t g_term_row;
static size_t g_term_col;
static uint8_t g_term_color;
static uint16_t* g_term_buffer;

void term_set(unsigned char c, size_t row, size_t col, uint8_t color);

void term_init() {
    g_term_row = 0;
    g_term_col = 0;
    g_term_color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    g_term_buffer = VGA_MEMORY;
    for (size_t row = 0; row < VGA_HEIGHT; ++row) {
        for (size_t col = 0; col < VGA_WIDTH; ++col) {
            term_set(' ', row, col, g_term_color);
        }
    }
}

void term_write(const char *data) {
    for (size_t i = 0; i < strlen(data); ++i) {
        term_set(data[i], g_term_row, ++g_term_col, g_term_color);
    }
}

void term_set(unsigned char c, size_t row, size_t col, uint8_t color) {
    g_term_buffer[row * VGA_WIDTH + col] = vga_entry(c, color);
}

