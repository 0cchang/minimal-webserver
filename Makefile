CC= gcc

main: main.c
	$(CC) main main.c -lWs2_32.lib

clean:
	rm *.out

