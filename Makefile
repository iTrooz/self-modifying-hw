
all:
	gcc main.c -o a.out -O0 -g
	objcopy --set-section-flags .text=contents,alloc,load,code a.out a.out2