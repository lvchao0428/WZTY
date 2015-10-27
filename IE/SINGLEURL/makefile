CFLAGE+= -g
OBJECT = main.o page.o test.o mystring.o myfiledeal.o lable_deal.o \
    discuz_extract.o nodiscuz_extract.o 
main:$(OBJECT)
	gcc -g -o main $(OBJECT) -lm
$(OBJECT):def.h
page.o main.o:page.h
main.o test.o:test.h
myfiledeal.o:myfiledeal.h
lable_deal.o:lable_deal.h
main.o discuz_extract.o:discuz_extract.h
main.o nodiscuz_extract.o:nodiscuz_extract.h
main.o test.o:test.h
mystring.o myfiledeal.o lable_deal.o discuz_extract.o nodiscuz_extract.o:mystring.h
.PHONY:clean
clean:
	rm *.o
