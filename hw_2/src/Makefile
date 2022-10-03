all:	result

result: matmul_lib.a
	gcc -O3 -g matmul_main.c matmul_lib.a -o result.out
	
matmul_lib.a: matmul_lib.o
	ar rc matmul_lib.a matmul_lib.o
	
matmul_lib.o: matmul_lib.c
	gcc -c -O3 -g matmul_lib.c
