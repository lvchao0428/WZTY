main:main.o savehtml.o code_convert.o
	gcc -o main main.o savehtml.o code_convert.o
main.o:main.o
	gcc -c main.c
savehtml.o:savehtml.c
	gcc -c savehtml.c
code_convert.o:code_convert.c
	gcc -c code_convert.c
clean:
	rm *.o main
