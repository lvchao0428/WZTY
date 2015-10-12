$(OBJECT):main.o page.o
main:main.o page.o
	gcc -g -o main main.o page.o
main.o:main.c
	gcc -g -c main.c
page.o:page.c
	gcc -g -c page.c
.PHONY:clean
clean:
	rm *.o
