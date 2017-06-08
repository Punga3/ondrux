#include <stdint.h>
char *alloc_base;
void mman_init(char *alloc_start){
	alloc_base=alloc_start;
}
void* malloc(uint32_t size){
	void *ret;
	ret=(void*)alloc_base;
	alloc_base+=size;
	return ret;
}
