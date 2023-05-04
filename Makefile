
CFLAGS = -W -Wall -pedantic -Ofast

#CC = armv7a-hardfloat-linux-gnueabi-gcc -static -mfpu=neon -march=armv7-a
#QEMU = qemu-arm

.PHONY: test
test: testbench
	$(QEMU) ./testbench 5 3

.PHONY: tables
tables: generate
	./generate

.PHONY: clean
clean:
	rm -f generate testbench

