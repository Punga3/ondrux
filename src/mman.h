#ifndef MMAN_H
#define MMAN_H
char *alloc_base;
void* malloc(uint32_t size);
void mman_init(char *alloc_start);
#endif
