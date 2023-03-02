test: minheap.c
	gcc -Wall -Werror minheap.c minheap_tester.c -o test
.PHONY: clean
clean:
	rm test