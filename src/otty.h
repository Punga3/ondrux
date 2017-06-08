#ifndef OTTY_H
#define OTTY_H
void print_str(char* text);
void print_str_ln(char* text);
void print_num(uint32_t n);
void print_num_ln(uint32_t n);
void print_num_base(uint32_t n,uint32_t b);
void print_num_hex(uint32_t n);
void hex_dump(uint32_t n);
void print_num_hex_ln(uint32_t n);
void otty_init();
void otty_clear();
void terminal_putchar(char c);
void terminal_scroll_rel(uint32_t delta);
#endif
