#ifndef ODIO_H
#define ODIO_H
void print_str(char* text);
void print_str_ln(char* text);
void print_num(uint32_t n);
void print_num_ln(uint32_t n);
void print_num_base(uint32_t n,uint32_t b);
void print_num_hex(uint32_t n);
void hex_dump(uint32_t n);
void print_num_hex_ln(uint32_t n);
void odio_init();
void odio_clear();
#endif
