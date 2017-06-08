# Constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# 16-byte aligned stack
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
.skip 1
idtr:
.skip 0x100
# Ondřux start point
.section .text
.global _start
.type _start, @function
_start:

	# Set stack pointer
	mov $stack_top, %esp

	# Push 
	push %eax
	push %ebx

	# Align
	# TODO

	# Call kernel
	call kernel_main

	# End 
	cli
1:	hlt
	jmp 1b

# Set the size of the _start symbol to the current location '.' minus its start.
.size _start, . - _start
