#ifndef MEMORY_H
#define MEMORY_H
void init_memory();
void print_mmap_info();
memory_map_t* mmap_start;
memory_map_t** mmap_array;
uint8_t mmap_array_len;
uint32_t ram_len;
#endif
