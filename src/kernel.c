#include <stdbool.h>
#include <stdint.h>
#include "odio.h"
#include "multiboot.h"
#include "memory.h"
void kernel_main(multiboot_info_t* mbd, unsigned int magic) {
	odio_init();
	if(magic!=0x2BADB002){
		print_str_ln("Unable to check multiboot magic value, terminating.");
		return;
	}
	init_memory(mbd);
	print_mmap_info();
	print_str_ln("Test!");
}
