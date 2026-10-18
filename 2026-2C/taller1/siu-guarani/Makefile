siu: siu.o
	g++ $^ -o $@

siu.o: siu.cpp
	g++ -std=c++17 -Wall -c $< -o $@

test: siu
	@for i in tests/*.in; do \
		[ -e "$$i" ] || continue; \
		if [ "$$(./siu < $$i)" = "$$(cat $${i%.in}.out)" ]; then \
			echo "PASS $$i"; \
		else \
			echo "FAIL $$i"; \
		fi; \
	done

clean:
	rm -f siu.o siu
