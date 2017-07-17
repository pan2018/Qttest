CC			= gcc
CFLAGS 		= -O -fPIC -Wall
SRCREAD 	= shmread.c
SRCWRITE	= shmwrite.c

all : shmread shmwrite
shmread : $(SRCREAD)
	gcc  -o  shmread shmread.c -lm
#   没有其他库
	#gcc -shared -W1,-soname,  base.o -o libbase.so.1.0.0 -lpthread
#	有其他库
#	gcc -shared -W1 ${OBJS} -o $(LIBOBJS) -L./ -lhprtprinter
#	mv $(LIBOBJS) ./bin/
	
shmwrite: shmwrite.c
	gcc  -o shmwrite shmwrite.c -lm
#	gcc test.o -o test -L./ -lbase
#	chmod 777 test
clean:
	rm -f *.o
	rm -f seml shmread shmwrite
#	rm -rf libbase.so test
clean1:
	rm *.o
	rm *.so.*
	rm test
	rm *.tmp
