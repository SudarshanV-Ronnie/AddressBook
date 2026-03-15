abp: main.o contact.o file.o
	gcc -o abp main.o contact.o file.o

main.o: main.c
	gcc -c main.c

contact.o: contact.c
	gcc -c contact.c

file.o: file.c
	gcc -c file.c

clean:
	rm -f *.o abp
