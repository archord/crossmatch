PERFIX = ../../lib
WCSTOOL = ${PERFIX}/wcstools-3.8.5
ASTROMETRY = ${PERFIX}/astrometry.net-0.38
CFITSIO = ${PERFIX}/cfitsio

#WCSTOOL = /home/xy/program/lib/wcstools-3.8.5/libwcs
#ASTROMETRY = /home/xy/program/lib/astrometry
#CFITSIO = /disk1/opt/basic/prog_os_20110130_from_pc49
POSTGRESQL = /usr

LDIR = -L ${WCSTOOL}/lib  -L ${ASTROMETRY}/lib  -L ${CFITSIO}/lib
IDIR = -I ${WCSTOOL}/include  -I ${ASTROMETRY}/include  -I ${CFITSIO}/include
LIBS = -lcfitsio -lm -lpq -lanutils -lpthread -lwcs -lbackend

ALL:crossmatch

crossmatch:
	gcc ${IDIR} function.c main.c -o crossmatch  ${LDIR} ${LIBS}

clean:
	rm -rf *.o crossmatch

