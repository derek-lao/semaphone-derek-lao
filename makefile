all: control.o write.o
	gcc -o control functions.o control.o
	gcc -o write functions.o write.o

write.o: write.c functions.h
	gcc -c write.c

control.o: control.c functions.h
	gcc -c control.c

functions.o: functions.c functions.h
	gcc -c functions.c

clean:
	rm *.o
	rm *~
