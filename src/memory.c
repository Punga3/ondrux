#include <stdint.h>
#include <stddef.h>
#include "multiboot.h"
#include "otty.h"
#define MULTIBOOT_FLAG_0 (0x1)
#define MULTIBOOT_FLAG_6 (0x1<<5)
#define MAX_MEMORY_REGIONS 256
memory_map_t* mmap_start;
memory_map_t* mmap_array[MAX_MEMORY_REGIONS];
uint64_t ram_len=0;
uint8_t mmap_array_len;
void init_memory(multiboot_info_t* mbd){
	if(!(mbd->flags&MULTIBOOT_FLAG_0)){
		print_str_ln("Unable to get memory info, terminating.");
		return;
	}
	if(!(mbd->flags&MULTIBOOT_FLAG_6)){
		print_str_ln("Unable to get memory map, terminating.");
		return;
	}
	print_str("Lower memory: ");
	print_num(mbd->mem_lower);
	print_str_ln(" kB");
	print_str("Upper memory: ");
	print_num(mbd->mem_upper);
	print_str_ln(" kB");
	print_str("Memory map length:");
	print_num_ln(mbd->mmap_length);
	uint8_t i = 0;
	mmap_start = (memory_map_t*) mbd->mmap_addr;
	memory_map_t* mmap = mmap_start;
	while((size_t)mmap < mbd->mmap_addr + mbd->mmap_length) {
		if(mmap->type==1){
			mmap_array[i++]=mmap;
			ram_len+=mmap->length_high*0xFFFFFFFF+mmap->length_low;
		}
		mmap = (memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(mmap->size) );
	}
	mmap_array_len=i;
}
void print_mmap_info(){
	uint8_t i;
	for(i=0;i<mmap_array_len;i++){
		memory_map_t* mmap = mmap_array[i];
		print_str("Memory region #");
		print_num(i);
		print_str(" type: ");
		print_str_ln(mmap->type==1?"RAM":"Other");
		print_str("Start adress: ");
		hex_dump(mmap->base_addr_high);
		print_str(":");
		hex_dump(mmap->base_addr_low);
		print_str_ln("");
		print_str("Start length: ");
		hex_dump(mmap->length_high);
		print_str(":");
		hex_dump(mmap->length_low);
		print_str_ln("");
	}
}
