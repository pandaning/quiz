CC ?= gcc
CFLAGS_common ?= -O0 -Wall -std=gnu99

EXEC = iterative recursive
all: $(EXEC)

iterative: iterative.c
	$(CC) $(CFLAGS_common) -o $@ $@.c

recursive: recursive.c
	$(CC) $(CFLAGS_common) -o $@ $@.c

run: 
	./iterative
	./recursive

perf:
	echo "echo 1 > /proc/sys/vm/drop_caches" | sudo sh
	perf stat -r 10000 -e cache-misses,cache-references,L1-dcache-load-misses,L1-dcache-store-misses,L1-dcache-prefetch-misses,L1-icache-load-misses ./recursive
	perf stat -r 10000 -e cache-misses,cache-references,L1-dcache-load-misses,L1-dcache-store-misses,L1-dcache-prefetch-misses,L1-icache-load-misses ./iterative

clean:
	$(RM) $(EXEC) *.o perf.*
	$(RM) q3_recursive.txt q3_iterative.txt
