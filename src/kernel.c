#include <stdbool.h>
#include <stdint.h>
#include "otty.h"
#include "multiboot.h"
#include "memory.h"
#include "ps2keyboard.h"
#include "mman.h"
#include "obish.h"
void kernel_main(multiboot_info_t* mbd, unsigned int magic) {
	otty_init();
	if(magic!=0x2BADB002){
		print_str_ln("Unable to check multiboot magic value, terminating.");
		return;
	}
	init_memory(mbd);
	print_mmap_info();
	while(getScancode()!='9');
	print_str_ln("Ondrux; version -1.0");
	print_str_ln("~~~~~~~~~~~~~~");
	print_str("RAM: ");
	print_num(ram_len);
	print_str_ln("B");
	print_str("Kernel end: ");
	extern char* __kernel_end;
	mman_init(__kernel_end);
	print_num_hex_ln((uint32_t)__kernel_end);
	obish();
}
