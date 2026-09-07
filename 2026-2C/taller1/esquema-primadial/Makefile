#   make        build the binary
#   make test   build, then run every tests/*.in against its *.out
#   make clean  remove objects and binary

piramidal: piramidal.o
	g++ $^ -o $@

piramidal.o: piramidal.cpp
	g++ -std=c++17 -Wall -c $< -o $@

test: piramidal
	@for i in tests/*.in; do \
		[ -e "$$i" ] || continue; \
		if [ "$$(./piramidal < $$i)" = "$$(cat $${i%.in}.out)" ]; then \
			echo "PASS $$i"; \
		else \
			echo "FAIL $$i"; \
		fi; \
	done

clean:
	rm -f piramidal.o piramidal
