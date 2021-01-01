#makefile for our crawler program
#variables
CC=gcc
CFLAG=-lcurl -ltidy -lpthread -Wall -I.

#tagets: Dependencies
	#actions
all: crawler
crawler: main.o spider.o crawler.o crawl_frontier.o hash.o queue.o
	$(CC) main.o spider.o crawler.o crawl_frontier.o hash.o queue.o -o crawler $(CFLAG) 
main.o: main.c
	$(CC) -c main.c
spider.o: spider.c
	$(CC) -c spider.c
crawler.o: crawler.c
	$(CC) -c crawler.c
crawl_frontier.o: crawl_frontier.c
	$(CC) -c crawl_frontier.c
hash.o: hash.c
	$(CC) -c hash.c
queue.o: queue.c
	$(CC) -c queue.c
#clean all the object files and crawler executable file.
clean:
	rm *.o crawler
