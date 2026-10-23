#   make        build the binary
#   make test   build, then run every tests/*.in against its *.out
#   make clean  remove objects and binary

gasoducto: gasoducto.o
	g++ $^ -o $@

gasoducto.o: gasoducto.cpp
	g++ -std=c++17 -Wall -c $< -o $@

test: gasoducto
	@for i in tests/*.in; do \
		[ -e "$$i" ] || continue; \
		if [ "$$(./gasoducto < $$i)" = "$$(cat $${i%.in}.out)" ]; then \
			echo "PASS $$i"; \
		else \
			echo "FAIL $$i"; \
		fi; \
	done

clean:
	rm -f gasoducto.o gasoducto
