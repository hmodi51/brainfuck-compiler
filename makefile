# Flags
OPTIMIZED =-O3 -march=native -mtune=native
CFLAGS =-nostdlib

# BF source file (defaulted to hello-word)
BF_SOURCE ?= examples/hello-world.bf


# Standard compilation commands
compile:
	gcc bf.c -o bf

output: compile 
	./bf $(BF_SOURCE)
	gcc $(CFLAGS) output.s -o output


##### Optimized for the LOLs #####
compile_optimized:
	gcc $(OPTIMIZED) bf.c -o bf

output_optimized: compile_optimized
	./bf $(BF_SOURCE)
	gcc $(CFLAGS) $(OPTIMIZED) output.s -o output

clean:
	rm -f bf output *.s