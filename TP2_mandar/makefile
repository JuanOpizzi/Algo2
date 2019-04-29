CFLAGS := -g -std=c99 -Wall -Wformat=2
CFLAGS += -Wunreachable-code
CFLAGS += -Wconversion -Wno-sign-conversion -Wbad-function-cast
CFLAGS += -Werror

VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

TWEETS = My_counting.o hash.o heap.o lista.o strutil.o  
USUARIOS = hash.o lista.o strutil.o 


all: $(TWEETS) $(USUARIOS)
	gcc $(CFLAGS) -o procesar_tweets $(TWEETS)  procesar_tweets.c 
	gcc $(CFLAGS) -o procesar_usuarios $(USUARIOS)  procesar_usuarios.c 
	rm *.o

lista.o:
	gcc $(CFLAGS) lista.c -c	

heap.o:  
	gcc $(CFLAGS) heap.c  -c

hash.o: 
	gcc $(CFLAGS) hash.c -c	

My_counting.o:
	gcc $(CFLAGS) My_counting.c -c

strutil.o:
	gcc $(CFLAGS) strutil.c -c	

clean:
	rm procesar_tweets procesar_usuarios 
	

run:
	valgrind $(VFLAGS) ./procesar_usuarios tweets_head.txt
	cat tweets_head.txt | valgrind $(VFLAGS) ./procesar_tweets 100 20
	cat tweets.txt | valgrind $(VFLAGS) ./procesar_tweets 300000 25	
	#Las pruebas pesadas
	#cat tweets.txt | valgrind $(VFLAGS) ./procesar_tweets 19000000 25
	#./procesar_usuarios tweets.txt
	#rm procesar_usuarios procesar_tweets












