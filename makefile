my_b64: b64.o my_b64.c
	gcc -o my_b64 b64.o my_b64.c

b64.o: b64.c
	gcc -c b64.c
