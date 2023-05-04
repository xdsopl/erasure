
CFLAGS = -W -Wall -pedantic -Ofast

CC = clang -march=native

#CC = armv7a-hardfloat-linux-gnueabi-gcc -static -mfpu=neon -march=armv7-a
#QEMU = qemu-arm

#CC = aarch64-unknown-linux-gnu-gcc -static
#QEMU = qemu-aarch64

.PHONY: test
test: testbench
	$(QEMU) ./testbench 5 3

.PHONY: tables
tables: generate
	./generate

.PHONY: clean
clean:
	rm -f generate testbench

