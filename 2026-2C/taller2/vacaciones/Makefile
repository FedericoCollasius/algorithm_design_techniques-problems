#   make        build the binary
#   make test   build, then run every tests/*.in against its *.out
#   make clean  remove objects and binary

vacaciones: vacaciones.o
	g++ $^ -o $@

vacaciones.o: vacaciones.cpp
	g++ -std=c++17 -Wall -c $< -o $@

test: vacaciones
	@for i in tests/*.in; do \
		[ -e "$$i" ] || continue; \
		if [ "$$(./vacaciones < $$i)" = "$$(cat $${i%.in}.out)" ]; then \
			echo "PASS $$i"; \
		else \
			echo "FAIL $$i"; \
		fi; \
	done

clean:
	rm -f vacaciones.o vacaciones
