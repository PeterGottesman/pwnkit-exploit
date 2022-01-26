.PHONY: default
default: test

BADCONV.so: badconv.c
	gcc -fPIC -shared $< -o $@

.PHONY: test
test: BADCONV.so
	GCONV_PATH=. iconv -f UTF-8 -t ZT <(echo hi)

.PHONY: clean
clean:
	rm BADCONV.so
