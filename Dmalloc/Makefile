default: mallocexample

CFLAGS = -g -std=c99 -I${HOME}/dmalloc/include -DDMALLOC -DDMALLOC_FUNC_CHECK

DMALLOC_LIB=-L${HOME}/dmalloc/lib -ldmalloc

LDLIBS=${DMALLOC_LIB}

mallocexample: mallocexample.o

clean: 
	rm -f mallocexample mallocexample.o
