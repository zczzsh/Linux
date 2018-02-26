server:server.o seml.o
	gcc server.o seml.o -o server -lpthread

customer:customer.o seml.o
	gcc customer.o seml.o -o customer -lpthread

server.o:server.c seml.h
	gcc server.c -c -lpthread

customer.o:customer.c seml.h
	gcc customer.c -c -lpthread

seml.o:seml.c seml.h
	gcc seml.c -c

.PHONY:clean

clean:
	-rm *.o server customer reset