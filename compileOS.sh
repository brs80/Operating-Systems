dd if=/dev/zero of=floppya.img bs=512 count=2880
dd if=/dev/zero of=floppya.img bs=512 count=2880
bcc -ansi -c -o kernel.o kernel.c
ld86 -o kernel -d kernel.o kasm.o
dd if=kernel of=floppya.img bs=512 conv=notrunc seek=259