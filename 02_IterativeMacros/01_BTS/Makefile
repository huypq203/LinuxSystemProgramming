TARGET: exe

exe: bts.o app.o
	gcc -o exe bts.o app.o

app.o: app.c
	gcc -o app.o app.c -c

bts.o: bts.c
	gcc -o bts.o bts.c -c

clear:
	rm app.o
	rm bts.o
	rm exe
