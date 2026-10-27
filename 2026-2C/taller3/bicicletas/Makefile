#   make        build the binary
#   make test   build, then run every tests/*.in against its *.out
#   make clean  remove objects and binary

bici: bici.o
	g++ $^ -o $@

bici.o: bici.cpp
	g++ -std=c++17 -Wall -c $< -o $@

test: bici
	@for i in tests/*.in; do \
		[ -e "$$i" ] || continue; \
		if [ "$$(./bici < $$i)" = "$$(cat $${i%.in}.out)" ]; then \
			echo "PASS $$i"; \
		else \
			echo "FAIL $$i"; \
		fi; \
	done

clean:
	rm -f bici.o bici
