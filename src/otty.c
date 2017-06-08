#include <stddef.h>
#include <stdint.h>

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

uint32_t strlen(const char* str) {
	uint32_t len = 0;
	while (str[len])
		len++;
	return len;
}

static const uint32_t VGA_WIDTH = 80;
static const uint32_t VGA_HEIGHT = 25;

uint32_t terminal_row;
uint32_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
uint16_t terminal_history[80][4096];
uint32_t terminal_history_index = 0;
uint32_t terminal_scroll_index = 0;

void otty_init(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREY);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (uint32_t y = 0; y < VGA_HEIGHT; y++) {
		for (uint32_t x = 0; x < VGA_WIDTH; x++) {
			const uint32_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, uint32_t x, uint32_t y) {
	const uint32_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
	terminal_history[terminal_history_index][x] = terminal_buffer[index];
}

void terminal_scroll(uint32_t value){
	terminal_scroll_index=value;
	uint32_t i = 0;
	for(;i<VGA_HEIGHT;i++){
		uint32_t j = 0;
		for(;j<VGA_WIDTH;j++){
			if(value+i<terminal_history_index){
				terminal_buffer[i*VGA_WIDTH+j]=terminal_history[value+i][j];
			}else{
				terminal_buffer[i*VGA_WIDTH+j]=vga_entry(' ', terminal_color);
			}
		}
	}
}

void terminal_scroll_rel(uint32_t delta){
	terminal_scroll(terminal_scroll_index+delta);
}

void terminal_putchar(char c) {
	if(c!='\n'){
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_row = 0;
		}
	}else{
		uint8_t i = terminal_column;
		for(;i<80;i++)
			terminal_history[terminal_history_index][i]=vga_entry(' ',terminal_color);
		terminal_column = 0;
		if (terminal_row+1 == VGA_HEIGHT){
			terminal_scroll(++terminal_scroll_index);
		}else{
			terminal_row++;
		}
		terminal_history_index++;
	}
}

void terminal_write(const char* data, uint32_t size) {
	for (uint32_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void print_str(const char* data) {
	terminal_write(data, strlen(data));
}
void print_str_ln(const char* data) {
	terminal_write(data, strlen(data));
	terminal_putchar('\n');
}

#define NUM_BUFFER_LEN 100

char num_buffer[NUM_BUFFER_LEN];

void print_num_base(uint32_t n,uint32_t base) {
	uint32_t i = 0;
	if(n==0){
		terminal_putchar('0');
		return;
	}
 	while(n>0&&i<NUM_BUFFER_LEN){
		uint32_t c = n%base;
		if(c<10){
			num_buffer[i++]=(char)c+0x30;
		}else{
			num_buffer[i++]=(char)c-10+0x41;
		}
		n/=base;
	}
	for(;i>0;i--){
		terminal_putchar(num_buffer[i-1]);
	}
}

void hex_dump(uint32_t n){
	uint32_t i = 0;
	while(n>0&&i<NUM_BUFFER_LEN){
		uint32_t c = n%16;
		if(c<10){
			num_buffer[i++]=(char)c+0x30;
		}else{
			num_buffer[i++]=(char)c-10+0x41;
		}
		n/=16;
	}
	uint32_t j = 0;
	for(j=8;j>i;j--){
		terminal_putchar('0');
	}
	for(;i>0;i--){
		terminal_putchar(num_buffer[i-1]);
	}
}

void print_num(uint32_t n) {
	print_num_base(n,10);
}

void print_num_ln(uint32_t n) {
	print_num_base(n,10);
	terminal_putchar('\n');
}

void print_num_hex(uint32_t n) {
	print_str("0x");
	print_num_base(n,16);
}

void print_num_hex_ln(uint32_t n) {
	print_str("0x");
	print_num_base(n,16);
	terminal_putchar('\n');
}

void otty_clear(){
	uint32_t i;
	for(i=0;i<VGA_WIDTH*VGA_HEIGHT;i++)
		terminal_putchar(' ');
	terminal_column=0;
	terminal_row=0;
}
