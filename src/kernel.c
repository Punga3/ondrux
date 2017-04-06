/* Surely you will remove the processor conditionals and this comment
   appropriately depending on whether or not you use C++. */
#include <stdbool.h> /* C doesn't have booleans by default. */
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
	//print_mmap_info();
	odio_clear();
	print_str("mmap adress: ");
	hex_dump((uint32_t)&mmap_start);
	print_str_ln("");
	extern char *__kernel_end;
	print_str_ln("");
	hex_dump((uint32_t)__kernel_end);
}
