i686-elf-as src/boot.s -o build/bin/boot.o
i686-elf-gcc -c src/kernel.c -o build/bin/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c src/odio.c -o build/bin/odio.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c src/memory.c -o build/bin/memory.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T linker.ld -o build/isodir/boot/ondřux.bin -ffreestanding -O2 -nostdlib build/bin/boot.o build/bin/kernel.o build/bin/odio.o build/bin/memory.o -lgcc
cp grub.cfg build/isodir/boot/grub/grub.cfg
grub-mkrescue -o build/iso/ondrux.iso build/isodir
