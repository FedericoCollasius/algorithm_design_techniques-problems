#   make        build the binary
#   make test   build, then run every tests/*.in against its *.out
#   make clean  remove objects and binary

consultas: consultas.o
	g++ $^ -o $@

consultas.o: consultas.cpp
	g++ -std=c++17 -Wall -c $< -o $@

test: consultas
	@for i in tests/*.in; do \
		[ -e "$$i" ] || continue; \
		if [ "$$(./consultas < $$i)" = "$$(cat $${i%.in}.out)" ]; then \
			echo "PASS $$i"; \
		else \
			echo "FAIL $$i"; \
		fi; \
	done

clean:
	rm -f consultas.o consultas
