a.out:app.o seq_list.o
	gcc app.o seq_list.o 

app.o:app.c
	gcc -c app.c -o app.o
seq_list.o:seq_list.c 
	gcc -c seq_list.c -o seq_list.o

.PHPNY:clean
clean:
	rm -rf a.out app.o seq_list.o
	
