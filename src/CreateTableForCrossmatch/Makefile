

prefix		= /usr
exec_prefix	= ${prefix}
DESTDIR		= 
PQ_LIB	= ${DESTDIR}${exec_prefix}/lib64
PQ_INCLUDE	= ${DESTDIR}${prefix}/include

IDIR = -I ${PQ_INCLUDE}
LDIR = -L ${PQ_LIB}
LIBS = -lpq

ALL:CreateTableForCrossmatch

CreateTableForCrossmatch:
	gcc function.c main.c -o CreateTableForCrossmatch ${LIBS}

clean:
	rm -rf CreateTableForCrossmatch

