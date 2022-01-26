.PHONY: default
default: run-exploit

exploit: exploit.c
	gcc -o $@ $<

gconv/BADCONV.so: gconv/badconv.c
	make -C ./gconv BADCONV.so

.PHONY: run-exploit
run-exploit: exploit gconv/BADCONV.so
	./exploit

.PHONY: clean
clean:
	rm exploit
	make -C ./gconv clean
