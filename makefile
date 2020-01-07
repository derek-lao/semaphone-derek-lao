all: control.o write.o
	gcc -o control control.o
	gcc -o write write.o

write.o: write.c functions.h
	gcc -c write.c

control.o: control.c functions.h
	gcc -c control.c

clean:
	rm *.o
	rm *~
