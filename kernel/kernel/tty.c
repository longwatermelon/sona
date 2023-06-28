#include <kernel/tty.h>
#include <kernel/vga.h>
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
void term_scroll();

void term_init()
{
    g_term_row = 0;
    g_term_col = 0;
    g_term_color = vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLUE);
    g_term_buffer = VGA_MEMORY;

    for (size_t row = 0; row < VGA_HEIGHT; ++row)
    {
        for (size_t col = 0; col < VGA_WIDTH; ++col)
            term_set(' ', row, col, g_term_color);
    }
}

void term_write(const char *data)
{
    for (size_t i = 0; i < strlen(data); ++i)
    {
        if (data[i] == '\n')
        {
            ++g_term_row;
            g_term_col = 0;
        }
        else
        {
            term_set(data[i], g_term_row, g_term_col++, g_term_color);
        }

        if (g_term_row >= VGA_HEIGHT)
        {
            term_scroll();
            g_term_row = VGA_HEIGHT - 1;
            g_term_col = 0;
        }
    }
}

void term_scroll()
{
    // Take (row + 1)'s contents and put it in row
    for (size_t row = 0; row < VGA_HEIGHT; ++row)
    {
        for (size_t col = 0; col < VGA_WIDTH; ++col)
        {
            // Move row + 1 into row
            size_t index = row * VGA_WIDTH + col;
            size_t below = index + VGA_WIDTH;
            g_term_buffer[index] = g_term_buffer[below];
        }
    }

    // Fill last row with spaces
    for (size_t col = 0; col < VGA_WIDTH; ++col)
        term_set(' ', VGA_HEIGHT - 1, col, g_term_color);
}

void term_set(unsigned char c, size_t row, size_t col, uint8_t color)
{
    g_term_buffer[row * VGA_WIDTH + col] = vga_entry(c, color);
}

void term_color(uint8_t color)
{
    g_term_color = color;
}

