TARGET: exe

exe: dll.o dll_util.o app.o
	gcc -o exe dll.o dll_util.o app.o

app.o: app.c
	gcc -o app.o app.c -c

dll.o: dll.c
	gcc -o dll.o dll.c -c

dll_util.o: dll_util.c
	gcc -o dll_util.o dll_util.c -c

clear:
	rm app.o
	rm dll.o
	rm dll_util.o
	rm exe
