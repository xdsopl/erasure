
CFLAGS = -W -Wall -pedantic -Ofast

.PHONY: test
test: testbench
	./testbench 5 3

.PHONY: tables
tables: generate
	./generate

.PHONY: clean
clean:
	rm -f generate testbench

