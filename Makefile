all: rtclock.o spintest.c blockingtest.c
	gcc -Wall -g -o spintest spintest.c rtclock.o -lpthread
	gcc -Wall -g -o blockingtest blockingtest.c rtclock.o -lpthread

rtclock.o: rtclock.h rtclock.c
	gcc -Wall -g -c rtclock.c

clean:
	rm -rf *.o blockingtest spintest
