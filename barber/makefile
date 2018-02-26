barber:barber.o 
	gcc barber.o -o barber -lpthread

barber.o:barber.c 
	gcc barber.c -c -lpthread

.PHONY:clean

clean:
	-rm *.o barber reset