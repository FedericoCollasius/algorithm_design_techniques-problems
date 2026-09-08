misterioso: misterioso.o
	g++ $^ -o $@

misterioso.o: misterioso.cpp
	g++ -std=c++17 -Wall -c $< -o $@

test: misterioso
	@for i in tests/*.in; do \
		[ -e "$$i" ] || continue; \
		if [ "$$(./misterioso < $$i)" = "$$(cat $${i%.in}.out)" ]; then \
			echo "PASS $$i"; \
		else \
			echo "FAIL $$i"; \
		fi; \
	done

clean:
	rm -f misterioso.o misterioso
