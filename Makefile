
.PHONY: test
test: testbench
	./testbench

.PHONY: tables
tables: generate
	./generate

.PHONY: clean
clean:
	rm -f generate testbench

